#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <complex>
#include <cmath>


using namespace std;

void print1D(vector<complex<double> > vec, string y){
    cout << "printe vec:"<< endl;
    for (int i =0; i< vec.size(); i ++){
        cout << y<<"="<< i << ":" << vec[i] << endl;
    }
}

void print2D(vector<vector<complex<double> > > f_xy, string x, string y){
    int M = f_xy.size();
    int N = f_xy[0].size();
    cout << "M=" << M << ", N=" << N << endl;
    cout << endl <<  "(" << x << "," << y << ")" << setw(15) << "real" << setw(10) << "imag" << endl << endl;
    for (int k = 0; k<M ; k++){
        for (int l = 0; l<N; l++){
       
        cout << "(" << k << " , "  << l  << ")" << setw(10) << f_xy[k][l].real()<< setw(10 ) << f_xy[k][l].imag()<< endl;
    }
    }
}

// f_xy ist M zeilige und N spaltige Matrix
vector<vector<complex<double> > > DFT_2D ( vector<vector<complex<double> > > f_xy){
    
    int M = f_xy.size();
    int N = f_xy[0].size();
    cout << M << setw(12) << N << endl;
    complex <double> sum_x;
    complex <double> sum_y;
    vector<vector<complex<double> > > F_kl;
    vector<complex<double> > vecl;
    


    // Auswertung über (k,l) mit k= 0,1,2,... N-1 & l =  0,1,2,... M-1
    for (int k = 0; k < M; k++){
        
        vector<complex<double> > vecl;
        for (int l = 0; l < N; l++){
            sum_x = complex<double>(0,0);
            

            for (int x = 0; x<M ; x++){
                // x=0: gibt uns die summe über alle y für x=0, x=1: ...
                sum_y = complex<double>(0,0);
                for (int y = 0; y<N ; y++){
                    sum_y += f_xy[x][y] * exp(complex<double>(0,-2*M_PI*( ((k*x)/M) +  ((l*y)/N))));
                    cout << "sum_y:" << sum_y << endl;
                    //cout << "y=" << y <<" beendet" << endl;
                }
                // summe über alle y für bestimmtes x auf sum_x addiert
                
                sum_x += sum_y;
            }
            // Summe zu konstanten
            vecl.push_back(sum_x);
            cout << "sum_x:" << sum_x << endl;
            
        }
        
        // an k-ter Stel le wird der Vektor mit allen l-Werte eingesetzt
        F_kl.push_back(vecl);
        print1D(vecl, "l");
    }

return F_kl;
}




int main(){

    int M = 50;    // Menge der x-Werte
    int N = 3;     // Menge der y-Werte

    // Vektor bestehen aus M N-dimensionale Vektoren
    vector<vector<complex<double> > > f_xy ;

    vector<complex<double> > f_vecy;
    f_vecy.reserve(N);

    double k = 3.0, l = 2.0;
    
    for (int x = 0; x<M ; x++){
        vector<complex<double> > f_vecy;
        for (int y = 0; y<N ; y++){
        complex<double> value = cos(((2*(M_PI)*k)/ static_cast<double>(M))*x)*cos(((2*(M_PI)*l)/ static_cast<double>(M))*y);
        f_vecy.push_back(value);
        }
        //print1D(f_vecy);
        f_xy.push_back(f_vecy);
        //cout << setw(5) << "x=" << x << endl;
        //print1D(f_xy[x], "y" );
    }

    //print2D(f_xy, "x", "y");
    
    
    vector<vector<complex<double> > > F_kl = DFT_2D(f_xy);
    
    //print2D(F_kl,"k", "l");
    cout << F_kl[1][2] << endl;
    cout << F_kl[7][2] << endl;
    return 0;
}