/* 	Array templates for arrays upto 5D. As can be seen, it can be easily		*/ 
/* 	modified to add higher dimensional arrays. If you do need higher     		*/
/* 	dimensional arrays, reconsider your profession :-);				*/
/* 	The arrays have 16-byte alignment so that vectorization is easier.		*/
/* 	Try to use as much of (smart) library calls as possible. If you need 		*/
/* 	to do somehing explicitly, try to write your code in a vectorizable  		*/
/* 	form. The arrays are assigned by their size in X, Y, Z...in that order. 	*/
/* 	However when accessing the arrays the reverse order is used.         		*/
/* 	V is the fastest increasing followed by W, X, Y, Z, ... .		        */
#ifndef __GUARD__
#define __GUARD__
#include <cstdio>
template <class T>
class MAT1D {
		float sizeofdata;
	public:
		T *data;
		MAT1D(long NX);
		MAT1D();
		void create(long NX);
		float size(){return sizeofdata;};
		~MAT1D();
		void clean();
		long sizex;
};

template <class T>
MAT1D <T>::MAT1D () {
};

template <class T>
MAT1D <T>::MAT1D (long NX) {
	if ((data = (T *) mkl_malloc(NX *sizeof(T), 128)) == NULL) {
		printf("Total memory requested is %f\n", (1.*NX*sizeof(T)/(1024*1024*1024)));
		perror("Memory not alloc'd for vector\n");
		exit(1);
	}
	sizex = NX;
//	std::fill(data, data+sizex, (T*)0.);
};

template <class T>
MAT1D <T>::~MAT1D() {
	mkl_free(data);
	data = NULL;
};

template <class T>
void MAT1D <T>::create (long NX) {
        if ((data = (T *) mkl_malloc(NX *sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %f\n", (1.*NX*sizeof(T)/(1024*1024*1024)));
                perror("Memory not alloc'd for vector\n");
                exit(1);
        }
        sizex = NX;
//      std::fill(data, data+sizex, (T*)0.);
};

template <class T>
void MAT1D <T>::clean() {
        mkl_free(data);
        data = NULL;
};

template <class T>
class MAT2D_NA {
                float sizeofdata;
        public:
		MAT2D_NA(long NX, long NY);
		~MAT2D_NA(void);
                T **data, *space;
		long sizex, sizey;
                void create(long NX, long NY);
                float size(){return sizeofdata;};
                void clean();           
};
/*
template <class T>
MAT2D<T>::MAT2D()
{
	sizeofdata = 0.;
	std::cout << "Creating 2D array" << std::endl;
}
*/

template <class T>
MAT2D_NA<T>::MAT2D_NA (long NX, long NY) {
int y;

        if ((space = (T *)malloc((NX*NY) * sizeof(T))) == NULL) {
                printf("Total memory requested is %f\n",(1.*NX*NY*sizeof(T)/(1024*1024*1024)));
                perror("Memory not allocd for whole block");
                exit(1);
        }

        if ((data = (T **)malloc(NY * sizeof(T *))) == NULL) {
                perror("Memory not allocd for z depth wise");
                exit(1);
        }
        for (y = 0; y < NY; y++) {
                (data)[y] = space + (y * NX);
        }

        sizeofdata = 1.*NX*NY*sizeof(T)/(1024*1024*1024);
	sizex = NX; sizey = NY;
}

template <class T>
MAT2D_NA<T>::~MAT2D_NA() {
        free(data);
        data = NULL;
        free(space);
        space = NULL;
}


template <class T>
class MAT2D {
                float sizeofdata;
        public:
		MAT2D(long NX, long NY);
		~MAT2D(void);
                T **data, *space;
		long sizex, sizey;
                void create(long NX, long NY);
                float size(){return sizeofdata;};
                void clean();           
		void resize(long NX, long NY);
};
/*
template <class T>
MAT2D<T>::MAT2D()
{
	sizeofdata = 0.;
	std::cout << "Creating 2D array" << std::endl;
}
*/

template <class T>
MAT2D<T>::MAT2D (long NX, long NY) {
int y;

        if ((space = (T *)mkl_malloc((NX*NY) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %f\n",(1.*NX*NY*sizeof(T)/(1024*1024*1024)));
                perror("Memory not allocd for whole block");
                exit(1);
        }

        if ((data = (T **)mkl_malloc(NY * sizeof(T *), 128)) == NULL) {
                perror("Memory not allocd for z depth wise");
                exit(1);
        }
        for (y = 0; y < NY; y++) {
                (data)[y] = space + (y * NX);
        }

        sizeofdata = 1.*NX*NY*sizeof(T)/(1024*1024*1024);
	sizex = NX; sizey = NY;
}

template <class T>
MAT2D<T>::~MAT2D() {
        mkl_free(data);
        data = NULL;
        mkl_free(space);
        space = NULL;
}

template <class T>
void MAT2D<T>::create (long NX, long NY) {
int y;

        if ((space = (T *)mkl_malloc((NX*NY) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %f\n",(1.*NX*NY*sizeof(T)/(1024*1024*1024)));
                perror("Memory not allocd for whole block");
                exit(1);
        }

        if ((data = (T **)mkl_malloc(NY * sizeof(T *), 128)) == NULL) {
                perror("Memory not allocd for z depth wise");
                exit(1);
        }
        for (y = 0; y < NY; y++) {
                (data)[y] = space + (y * NX);
        }

        sizeofdata = 1.*NX*NY*sizeof(T)/(1024*1024*1024);
        sizex = NX; sizey = NY;
}


template <class T>
void MAT2D<T>::resize (long NX, long NY) 
{
int y;
	if ((space = (T *)mkl_realloc(space, (NX*NY) * sizeof(T))) == NULL) 
	{
                printf("Total memory requested is %f\n",(1.*NX*NY*sizeof(T)/(1024*1024*1024)));
                perror("Memory not allocd for whole block");
                exit(1);
        }
	if ((data = (T **)mkl_realloc(data, NY * sizeof(T *))) == NULL) {
                perror("Memory not allocd for z depth wise");
                exit(1);
        }
        for (y = 0; y < NY; y++) {
                (data)[y] = space + (y * NX);
        }

        sizeofdata = 1.*NX*NY*sizeof(T)/(1024*1024*1024);
        sizex = NX; sizey = NY;
}

template <class T>
void MAT2D<T>::clean() {
        mkl_free(data);
        data = NULL;
        mkl_free(space);
        space = NULL;
}

template <class T>
class MAT3D {
                float sizeofdata;
		long nz;
        public:
		MAT3D(long NX, long NY, long NZ);
		~MAT3D(void);
                T ***data, *space;
		long sizex, sizey, sizez;
                void create(long NX, long NY, long NZ);
                float size(){return sizeofdata;};
                void clean();
};

template <class T>
MAT3D<T>::MAT3D (long NX, long NY, long NZ) {
long y, z;
        if ((space = (T *)mkl_malloc((NX*NY*NZ) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %ld\n",(NX*NY*NZ));
                perror("Memory not allocd for whole block");
                exit(1);
        }
        if ((data = (T ***)mkl_malloc(NZ * sizeof(T **), 128)) == NULL) {
                perror("Memory not allocd for z depth wise");
                exit(1);
        }
        for (z = 0; z < NZ; z++)
        {
                if(((data)[z] = (T **)mkl_malloc(NY * sizeof(T *), 128)) == NULL) {
                        perror("Memory not allocd slice wise");
                        exit(1);
                }
                for (y = 0; y < NY; y++)
                {
                        (data)[z][y] = space + (z*(NX * NY) + y*NX);
                }
        }


        sizeofdata = 1.*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
        sizex = NX; sizey = NY; sizez = NZ;
	nz = NZ;
}


template <class T>
void MAT3D<T>::create (long NX, long NY, long NZ) {
long y, z;
	nz = NZ;
        if ((space = (T *)mkl_malloc((NX*NY*NZ) * sizeof(T), 128)) == NULL) {                             
                printf("Total memory requested is %ld\n",(NX*NY*NZ));                             
                perror("Memory not allocd for whole block");                                            
                exit(1);                                                                                
        }
        if ((data = (T ***)mkl_malloc(NZ * sizeof(T **), 128)) == NULL) {                                    
                perror("Memory not allocd for z depth wise");                                           
                exit(1);                                                                                
        }
        for (z = 0; z < NZ; z++)                                                                      
        {       
                if(((data)[z] = (T **)mkl_malloc(NY * sizeof(T *), 128)) == NULL) {                          
                        perror("Memory not allocd slice wise");                                         
                        exit(1);                                                                        
                }
                for (y = 0; y < NY; y++)                                                              
                {       
                        (data)[z][y] = space + (z*(NX * NY) + y*NX);                           
                }                                                                                       
        }                                                                                               


        sizeofdata = 1.*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
	sizex = NX; sizey = NY; sizez = NZ;
}



template <class T>
void MAT3D<T>::clean() {
int i;
	for (i = 0; i < nz; i++) {
        	mkl_free((data)[i]);
                (data)[i] = NULL;
        }
        mkl_free(data);
        data = NULL;
        mkl_free(space);
        space = NULL;
}



template <class T>
MAT3D<T>::~MAT3D() {
        for (long i = 0; i < nz; i++) {
                mkl_free((data)[i]);
                (data)[i] = NULL;
        }
        mkl_free(data);
        data = NULL;
        mkl_free(space);
        space = NULL;
}


template <class T>
class MAT4D {
                float sizeofdata;
                long nz, ny;
        public:
                T ****data, *space;
		long sizex, sizey, sizez, sizew;
                MAT4D(long NW, long NX, long NY, long NZ);
		void create(long NW, long NX, long NY, long NZ);
                float size(){return sizeofdata;};
                ~MAT4D();
		void clean();
};

template <class T>
MAT4D<T>::MAT4D (long NW, long NX, long NY, long NZ) {
long w, x, y, z;
	nz = NZ; ny = NY;
        if ((space = (T *)mkl_malloc((NX*NY*NZ*NW) * sizeof(T), 128)) == NULL) 
	{
                printf("Total memory requested is %ld\n",(NX*NY*NZ*NW));
                perror("Memory not allocd for whole 4D block");
                exit(1);
        }
        if ((data = (T ****)mkl_malloc(NZ * sizeof(T ***), 128)) == NULL) 
	{
                perror("Memory not allocd for z depth wise-3D cubes");
                exit(1);
        }
        for (z = 0; z < NZ; z++)
        {
                if(((data)[z] = (T ***)mkl_malloc(NY * sizeof(T **), 128)) == NULL) 
		{
                        perror("Memory not allocd slice wise");
                        exit(1);
                }
                for (y = 0; y < NY; y++) 
		{
                        if(((data)[z][y] = (T **)mkl_malloc(NX * sizeof(T *), 128)) == NULL) 
			{
                                perror("Memory not allocd slice wise");
                                exit(1);
                        }
                        for (x = 0; x < NX; x++)
                        {
                                (data)[z][y][x] = space + (z*(NW * NX * NY)+y*(NW*NX)+ x*NW);
                        }
                }
        }
	sizeofdata = 1.*NW*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
	sizex = NX; sizey = NY; sizez = NZ; sizew = NW;
}

template <class T>
MAT4D <T>::~MAT4D() {
int i, j, k;
        for (i = 0; i < nz; i++) {
                for (j = 0; j < ny; j++) {
                        mkl_free((data)[i][j]);
                        (data)[i][j] = NULL;
                }
                mkl_free((data)[i]);
                (data)[i] = NULL;
        }
        mkl_free(data);
        (data) = NULL;
        mkl_free(space);
        (space) = NULL;
}

template <class T>
void MAT4D<T>::create (long NW, long NX, long NY, long NZ) {
long w, x, y, z;
	nz = NZ; ny = NY;
        if ((space = (T *)mkl_malloc((NX*NY*NZ*NW) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %ld\n",(NX*NY*NZ*NW));
                perror("Memory not allocd for whole 4D block");
                exit(1);
        }
        if ((data = (T ****)mkl_malloc(NZ * sizeof(T ***), 128)) == NULL) {
                perror("Memory not allocd for z depth wise-3D cubes");
                exit(1);
        }
        for (z = 0; z < NZ; z++)
        {
                if(((data)[z] = (T ***)mkl_malloc(NY * sizeof(T **), 128)) == NULL) {
                        perror("Memory not allocd slice wise");
                        exit(1);
                }
                for (y = 0; y < NY; y++) {
                        if(((data)[z][y] = (T **)mkl_malloc(NX * sizeof(T *), 128)) == NULL) {
                                perror("Memory not allocd slice wise");
                                exit(1);
                        }
                        for (x = 0; x < NX; x++)
                        {
                                (data)[z][y][x] = space + (z*(NW * NX * NY)+y*(NW*NX)+ x*NW);
                        }
                }
        }
	sizeofdata = 1.*NW*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
	sizex = NX; sizey = NY; sizez = NZ; sizew = NW;
}

template <class T>
void MAT4D <T>::clean() {
int i, j, k;
        for (i = 0; i < nz; i++) {
                for (j = 0; j < ny; j++) {
                        mkl_free((data)[i][j]);
                        (data)[i][j] = NULL;
                }
                mkl_free((data)[i]);
                (data)[i] = NULL;
        }
        mkl_free(data);
        (data) = NULL;
        mkl_free(space);
        (space) = NULL;
}

template <class T>
class MAT5D {
                float sizeofdata;
                long nz, ny, nx;
        public:
                T *****data, *space;
		MAT5D(long NV, long NW, long NX, long NY, long NZ);
                void create(long NV, long NW, long NX, long NY, long NZ);
                float size(){return sizeofdata;};
		~MAT5D();
                void clean();
};

template <class T>
MAT5D<T>::MAT5D (long NV, long NW, long NX, long NY, long NZ) {
long w, x, y, z;
        nz = NZ; ny = NY; nx = NX;
        if ((space = (T *)mkl_malloc((NV*NW*NX*NY*NZ) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %ld\n",(NX*NY*NZ*NW));
                perror("Memory not allocd for whole 5D block");
                exit(1);
        }
        if ((data = (T *****)mkl_malloc(NZ * sizeof(T ****), 128)) == NULL) {
                perror("Memory not allocd for z depth wise-3D cubes");
                exit(1);
        }
        for (z = 0; z < NZ; z++)
        {
                if(((data)[z] = (T ****)mkl_malloc(NY * sizeof(T ***), 128)) == NULL) {
                        perror("Memory not allocd slice wise");
                        exit(1);
                }
                for (y = 0; y < NY; y++) {
                        if(((data)[z][y] = (T ***)mkl_malloc(NX * sizeof(T **), 128)) == NULL) {
                                perror("Memory not allocd slice wise");
                                exit(1);
                        }
                        for (x = 0; x < NX; x++)
                        {
				if(((data)[z][y][x] = (T **)mkl_malloc(NW * sizeof(T *), 128)) == NULL) {
                                perror("Memory not allocd slice wise"); 
                                exit(1);
                        	}
				for (w = 0; w < NW; w++)
                        	{
                                	(data)[z][y][x][w] = space + (z*(NV * NW * NX * NY)+y*(NV * NW * NX)+ x*(NV * NW) + w * NV);
                        	}
                        }
                }
        }
        sizeofdata = 1.*NV*NW*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
}

template <class T>
MAT5D <T>::~MAT5D() {
int i, j, k;
        for (i = 0; i < nz; i++) {
                for (j = 0; j < ny; j++) {
			for (k = 0; k < nx; k++) {
                        	mkl_free((data)[i][j][k]);
                        	(data)[i][j][k] = NULL;
                	}
                	mkl_free((data)[i][j]);
                	(data)[i][j] = NULL;
        	}
		mkl_free((data)[i]);
		(data)[i] = NULL;
	}
        mkl_free(data);
        (data) = NULL;
        mkl_free(space);
        (space) = NULL;
}

template <class T>
void MAT5D<T>::create (long NV, long NW, long NX, long NY, long NZ) {
long w, x, y, z;
        nz = NZ; ny = NY; nx = NX;
        if ((space = (T *)mkl_malloc((NV*NW*NX*NY*NZ) * sizeof(T), 128)) == NULL) {
                printf("Total memory requested is %ld\n",(NX*NY*NZ*NW));
                perror("Memory not allocd for whole 5D block");
                exit(1);
        }
        if ((data = (T *****)mkl_malloc(NZ * sizeof(T ****), 128)) == NULL) {
                perror("Memory not allocd for z depth wise-3D cubes");
                exit(1);
        }
        for (z = 0; z < NZ; z++)
        {
                if(((data)[z] = (T ****)mkl_malloc(NY * sizeof(T ***), 128)) == NULL) {
                        perror("Memory not allocd slice wise");
                        exit(1);
                }
                for (y = 0; y < NY; y++) {
                        if(((data)[z][y] = (T ***)mkl_malloc(NX * sizeof(T **), 128)) == NULL) {
                                perror("Memory not allocd slice wise");
                                exit(1);
                        }
                        for (x = 0; x < NX; x++)
                        {
				if(((data)[z][y][x] = (T **)mkl_malloc(NW * sizeof(T *), 128)) == NULL) {
                                perror("Memory not allocd slice wise"); 
                                exit(1);
                        	}
				for (w = 0; w < NW; w++)
                        	{
                                	(data)[z][y][x][w] = space + (z*(NV * NW * NX * NY)+y*(NV * NW * NX)+ x*(NV * NW) + w * NV);
                        	}
                        }
                }
        }
        sizeofdata = 1.*NV*NW*NX*NY*NZ*sizeof(T)/(1024*1024*1024);
}

template <class T>
void MAT5D <T>::clean() {
int i, j, k;
        for (i = 0; i < nz; i++) {
                for (j = 0; j < ny; j++) {
			for (k = 0; k < nx; k++) {
                        	mkl_free((data)[i][j][k]);
                        	(data)[i][j][k] = NULL;
                	}
                	mkl_free((data)[i][j]);
                	(data)[i][j] = NULL;
        	}
		mkl_free((data)[i]);
		(data)[i] = NULL;
	}
        mkl_free(data);
        (data) = NULL;
        mkl_free(space);
        (space) = NULL;
}
#endif
