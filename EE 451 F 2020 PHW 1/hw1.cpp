//
//  hw1.cpp
//  
//
//  Created by hujunqi on 2020/8/23.
//

#include "hw1.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
    int n = 4096;
    
    cout<<"enter the number of row=";
    cin>>r;
    cout<<"enter the number of column=";
    cin>>c;
    cout<<"enter the first matrix element=\n";
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            cin>>a[i][j]
        }
    }
    
    cout<<"enter the second matrix element=\n";
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            cin>>b[i][j];
        }
    }
    
    cout<<"multiply of the matrix=\n";
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            mul[i][j]=0;
            for (int k=0; k<c; k++) {
                mul[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    
    
}


