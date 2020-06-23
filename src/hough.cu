/**
 * Computing coordinates of poinnts into Hough space 
 * must be called on length(X) blocks with length(sin_theta) threads per block.
 * 
* int* X, coordinate x of point
* int* Y, coordinate y of point 
* int* OUT, output image of size rho_len x length(sin_theta)
* float* sin_theta, - sinus value calculated for theta vector
* float* cos_theta, - cosinus value calculated for theta
* float rho_resolution, - resolutin of rho
* float rho_len, - number of rows in OUT image 
*
* y = a*x + b
*    |
*    V
* rho = x*sin(theta) + y*cos(theta)
*/
__global__ void hough(	int* X, 
						int* Y, 
						int* OUT, 
						float* sin_theta,
						float* cos_theta,
						float rho_resolution,
						int rho_len)
	{
	// int index = blockIdx.x*blockDim.x+threadIdx.x;
	int theta_idx = threadIdx.x;
	int point_idx = blockIdx.x;
	int theta_len = blockDim.x;
	
	// comute rho value 
	float rho = X[point_idx]*cos_theta[theta_idx] + Y[point_idx]*sin_theta[theta_idx];
	// divide rho by resolution, floor it and add middle value index as position of zero
	int rho_idx = int(rho/rho_resolution) + rho_len/2;
	
	// if rho index is in OUT image range
//	if (rho_idx >= 0 && rho_idx < rho_len)
		// increment point to OUT image
//		atomicAdd(OUT + rho_idx*theta_len + rho_idx, 1);	

    OUT[point_idx*theta_len + theta_idx] = 5;
    }
