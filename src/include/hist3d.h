#ifndef hist3d_h
#define hist3d_h

class Hist3D {
    public:
        Hist3D(const double& xmin, const double& xmax, const int& nx,
                const double& ymin, const double& ymax, const int& ny,
                const double& zmin, const double& zmax, const int& nz);
        ~Hist3D();
        
        void Fill(const double& x, const double& y, const double& z,
                const double& weight=1);
        
        long GetEntries() const;
        
        double GetXBinCenter(const int& ix);
        double GetXBinCenter(const double& x);
        
        double GetYBinCenter(const int& iy);
        double GetYBinCenter(const double& y);
        
        double GetZBinCenter(const int& iz);
        double GetZBinCenter(const double& z);
        
        double GetContent(const long& entry) const;
        double GetContent(const int& ix, const int& iy, const int& iz) const;
        
        double GetContent2(const long& entry) const;
        double GetContent2(const int& ix, const int& iy, const int& iz) const;
    
    private:
        double * weights[2];
        long entries;
};

#endif
