#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
              int N, double kernel[][11]);
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void gaussian(double k[][11], int N, double sigma);
void gaussian_filter(unsigned char out[][SIZE][RGB],
              unsigned char in[][SIZE][RGB], 
              int N, double sigma);
void unsharp(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
              int N, double sigma, double alpha);
//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[])
{
   //First check argc
  if(argc < 3)
    {
      //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
      return -1;
    }
   //then check to see if we can open the input file
   unsigned char input[SIZE][SIZE][RGB];
   unsigned char output[SIZE][SIZE][RGB];
   char* outfile;
   int N;
   double sigma, alpha;
   //double kernel[11][11];

   // read file contents into input array
   int status = readRGBBMP(argv[1], input); 
   if(status != 0)
   {
      cout << "unable to open " << argv[1] << " for input." << endl;
      return -1;
   }
   //Input file is good, now look at next argument
   if( strcmp("sobel", argv[2]) == 0)
   {
     sobel(output, input);
     outfile = argv[3];
   }
   else if( strcmp("blur", argv[2]) == 0)
   {
     if(argc < 6)
       {
	 cout << "not enough arguments for blur." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     outfile = argv[5];
     gaussian_filter(output, input, N, sigma);
   }
   else if( strcmp("unsharp", argv[2]) == 0)
   {
     if(argc < 7)
       {
	 cout << "not enough arguments for unsharp." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     alpha = atof(argv[5]);
     outfile = argv[6];
     unsharp(output, input, N, sigma, alpha);

   }
   else if( strcmp("dummy", argv[2]) == 0)
   {
     //do dummy
     dummy(output, input);
     outfile = argv[3];
   }
   else
   {
      cout << "unknown filter type." << endl;
      return -1;
   }

   if(writeRGBBMP(outfile, output) != 0)
   {
      cout << "error writing file " << argv[3] << endl;
   }

}   

#endif 

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   for (int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         k[i][j] = 0;
      }
   }
   k[1][1] = 1;
   convolve(out, in, 3, k);
}


// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the 
//  instructions in the comments
void convolve(unsigned char out[][SIZE][RGB], 
        unsigned char in[][SIZE][RGB], 
	      int N, double kernel[][11])
{
 
   int padded[SIZE+10][SIZE+10][RGB];  // Use for input image with appropriate 
                                       // padding
   int temp[SIZE][SIZE][RGB];          // Use for the unclamped output pixel 
                                       // values then copy from temp to out, 
                                       // applying clamping 

   //first set all of padded to 0 (black)
   for (int i = 0; i < SIZE+10; i++) {
     for (int j = 0; j < SIZE+10; j++) {
       for (int k = 0; k < RGB; k++) {
         padded[i][j][k] = 0; 
       }
     }
   }
  
   //now copy input into padding to appropriate locations
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {
          padded[i+N/2][j+N/2][k] = in[i][j][k]; 
       }    
     }
   }

   //initialize temp pixels to 0 (black)
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {
         temp[i][j][k] = 0; 
       }
     }
   }

  //now perform convolve (using convolution equation on each pixel of the 
  // actual image) placing the results in temp (i.e. unclamped result)
  //Here we give you the structure of the convolve for-loops, you need
  //to figure out the loop limits
  for(int y = 0; y < SIZE; y++)
    for(int x = 0; x < SIZE; x++)
      for(int k = 0 ; k < RGB; k++)
         for(int i = -N/2; i<= N/2; i++)
            for(int j= -N/2; j<= N/2; j++)
                  temp[y][x][k] += padded[y+i+N/2][x+j+N/2][k]
                  *kernel[i+N/2][j+N/2];


   //now clamp and copy to output
   // You may need to cast to avoid warnings from the compiler:
   // (i.e. out[i][j][k] = (unsigned char) temp[i][j][k];)
   
  //clamp
  for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {
         //clamp the upper bound 
         if (temp[i][j][k] > 255) {
           temp[i][j][k] = 255; 
         }
         //clamp the lower bound
         if (temp[i][j][k] < 0) {
           temp[i][j][k] = 0; 
         }
       }
     }
   }
   //copy 
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        out[i][j][k] = (unsigned char) temp[i][j][k]; 
      }
    }
  }
}

// You will need to complete this function by following the 
//  instructions in the comments
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   double s_h1[3][3] = { {-1, 0, 1}, 
                         {-2, 0, 2}, 
                         {-1, 0, 1} };
   double s_h2[3][3] = { {1, 0, -1}, 
                         {2, 0, -2}, 
                         {1, 0, -1} };
   
   unsigned char h1_sobel[SIZE][SIZE][RGB]; //hold intemediate images
   unsigned char h2_sobel[SIZE][SIZE][RGB]; 

   for (int i = 0; i < 11; i++)
   {
      for(int j=0; j < 11; j++)
      {
         k[i][j] = 0;
      }
   }

   // Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 3; j++) {
       //replace each element in k with the elements in s_h1 and print 
       k[i][j] = s_h1[i][j]; 
     }
   }

   // Call convolve to apply horizontal sobel kernel with result in h1_sobel
   convolve(h1_sobel, in, 3, k); 

   // Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 3; j++) {
       //replace each element in k with the elements in s_h2
       k[i][j] = s_h2[i][j]; 
     }
   }

   // Call convolve to apply horizontal sobel kernel with result in h2_sobel
   convolve(h2_sobel, in, 3, k); 

   // Add the two results (applying clamping) to produce the final output 
   int temp; 
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int x = 0; x < RGB; x++) {
         //perform clamping
         temp = h1_sobel[i][j][x] + h2_sobel[i][j][x]; 
         //upper bound
         if (temp > 255) {
           temp = 255; 
         }
         //lower bound
         else if (temp < 0) {
           temp = 0; 
         }
         //assign values 
         out[i][j][x] = (unsigned char) temp; 
       }
     }
   }
}


// Add the rest of your functions here (i.e. gaussian, gaussian_filter, unsharp)

//Gaussian Function
void gaussian(double k[][11], int N, double sigma) {
  //raw gaussian num
  double sum = 0; 
  double x = 0; 
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      //utilize Gaussian equation 
      x = -((pow(i-N/2, 2)/(2*pow(sigma, 2)))
            + (pow(j-N/2, 2)/(2*pow(sigma,2))));
      k[i][j] = exp(x); 
      sum += k[i][j]; 
    }
  }
  //normalized gaussian kernel
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      k[i][j] = k[i][j] / sum; 
    }
  }  
}

//Gaussian Filter - Blur Function 
void gaussian_filter(unsigned char output[][SIZE][3],
               unsigned char input[][SIZE][3], 
               int N, double sigma) {
  //create the kernel
  double k[11][11]; 
  //call other functions 
  gaussian(k, N, sigma); 
  convolve(output, input, N, k); 
}

//Unsharp Filter
void unsharp (unsigned char output[][SIZE][3],
              unsigned char input[][SIZE][3], 
              int N, double sigma, double alpha) {
  unsigned char temp[SIZE][SIZE][RGB]; 
  //calc difference between temp and input
  int dif = 0; 
  gaussian_filter(temp, input, N, sigma); 
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        //calculate the difference
        dif = input[i][j][k] - temp[i][j][k]; 
        dif = (int) (dif*alpha + input[i][j][k]); 
        //clamp 
        if (dif > 255) {
          dif = 255; 
        }
        else if (dif < 0) {
          dif = 0; 
        }
        //assign difference value 
        output[i][j][k] = (unsigned char) dif; 
      }
    }
  }
}


