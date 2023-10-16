#include "hist3d.h"
/* C++ API */
#include <cfloat>
#include <cmath>

static struct HistData {
    double xmin, xmax, xdelta;
    double ymin, ymax, ydelta;
    double zmin, zmax, zdelta;
    int nx, ny, nz;
} histData;

static int getBin(const double& value, const double& min,
        const double& delta, const int& n);

static long getIndex(const int& ix, const int& iy, const int& iz);

Hist3D::Hist3D(const double& xmin, const double& xmax, const int& nx,
        const double& ymin, const double& ymax, const int& ny,
        const double& zmin, const double& zmax, const int& nz) {
    histData.xmin = xmin;
    histData.xmax = xmax;
    histData.nx = nx < 2 ? 2 : nx;
    histData.xdelta = (xmax - xmin) / (histData.nx - 1);
    histData.ymin = ymin;
    histData.ymax = ymax;
    histData.ny = ny < 2 ? 2 : ny;
    histData.ydelta = (ymax - ymin) / (histData.ny - 1);
    histData.zmin = zmin;
    histData.zmax = zmax;
    histData.nz = nz < 2 ? 2 : nz;
    histData.zdelta = (zmax - zmin) / (histData.nz - 1);    
    this->entries = (histData.nx - 1) * (histData.ny - 1) * (histData.nz - 1);
    this->weights[0] = new double[this->entries];
    this->weights[1] = new double[this->entries];
    long i;
    for(i = 0; i < this->entries; i++) {
        this->weights[1][i] = this->weights[0][i] = 0.;
    }
}

Hist3D::~Hist3D() {
    delete[] weights[0];
    delete[] weights[1];
}

void Hist3D::Fill(const double& x, const double& y, const double& z,
        const double& weight) {
    const int ix = getBin(x, histData.xmin, histData.xdelta, histData.nx);
    const int iy = getBin(y, histData.ymin, histData.ydelta, histData.ny);
    const int iz = getBin(z, histData.zmin, histData.zdelta, histData.nz);
    
    if(ix < 0 || iy < 0 || iz < 0) return;
    
    long index = getIndex(ix, iy, iz);
    this->weights[0][index] += weight;
    this->weights[1][index] += weight*weight;
}

long Hist3D::GetEntries() const {
    return this->entries;
}

double Hist3D::GetXBinCenter(const int& ix) {
    if(ix < 0 || ix >= histData.nx - 1) return DBL_MAX;
    return histData.xmin + (ix + 0.5) * histData.xdelta;
}

double Hist3D::GetXBinCenter(const double& x) {
    const int ix = getBin(x, histData.xmin, histData.xdelta, histData.nx);
    return this->GetXBinCenter(ix);
}

double Hist3D::GetYBinCenter(const int& iy) {
    if(iy < 0 || iy >= histData.ny - 1) return DBL_MAX;
    return histData.ymin + (iy + 0.5) * histData.ydelta;
}

double Hist3D::GetYBinCenter(const double& y) {
    const int iy = getBin(y, histData.ymin, histData.ydelta, histData.ny);
    return this->GetYBinCenter(iy);
}

double Hist3D::GetZBinCenter(const int& iz) {
    if(iz < 0 || iz >= histData.nz - 1) return DBL_MAX;
    return histData.zmin + (iz + 0.5) * histData.zdelta;
}

double Hist3D::GetZBinCenter(const double& z) {
    const int iz = getBin(z, histData.zmin, histData.zdelta, histData.nz);
    return this->GetZBinCenter(iz);
}

double Hist3D::GetContent(const long& entry) const {
    if(entry < 0 || entry >= this->entries) return DBL_MAX;
    return this->weights[0][entry];
}

double Hist3D::GetContent(const int& ix, const int& iy, const int& iz) const {
    if(ix < 0 || ix >= histData.nx - 1 ||
            iy < 0 || iy >= histData.ny - 1 ||
            iz < 0 || iz >= histData.nz - 1) return DBL_MAX;
    return this->GetContent(getIndex(ix, iy, iz));
}

double Hist3D::GetContent2(const long& entry) const {
    if(entry < 0 || entry >= this->entries) return DBL_MAX;
    return this->weights[1][entry];
}

double Hist3D::GetContent2(const int& ix, const int& iy, const int& iz) const {
    if(ix < 0 || ix >= histData.nx - 1 ||
            iy < 0 || iy >= histData.ny - 1 ||
            iz < 0 || iz >= histData.nz - 1) return DBL_MAX;
    return this->GetContent2(getIndex(ix, iy, iz));
}

int getBin(const double& value, const double& min,
        const double& delta, const int& n) {
    const int index = std::floor((value - min) / delta + 0.5);
    if(index < 0 || index >= n - 1) return -1;
    return index;
}

long getIndex(const int& ix, const int& iy, const int& iz) {
    return ix * (histData.ny - 1) * (histData.nz - 1) + iy * (histData.nz - 1) + iz;
}
