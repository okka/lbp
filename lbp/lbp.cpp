//okba lanabi cs master2
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <math.h>


using namespace std;


IplImage * lbp(IplImage *img , CvMat *mat){
	int i,j,size=3;
	  int height,width,step,channels;

	  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  
  int tab[256];
		
		for(int u=0; u<256; u++){
			tab[u]=0;
		}
	 IplImage* img1 = cvCreateImage( cvGetSize(img), img->depth, img->nChannels );
    for(i=size/2;i<height-size/2;i++) for(j=size/2;j<width-size/2;j++) 
	{
		
		CvScalar s;
		int ii,jj;
		double sum;
		
		int k=0;
		CvScalar t;
		int res=0;
		CvScalar v= cvGet2D(img,i,j);
		for(ii=0;ii<size;ii++) for(jj=0;jj<size;jj++)
		{			
			
			t=cvGet2D(img,i+(ii-(size/2)),j+(jj-(size/2)));
			sum=  cvmGet(mat,ii,jj);
			
			if(t.val[0]<v.val[0]){
				res+=0;
			}
			else{
				res+=1*sum;
			}
					
		}
		tab[res]+=1;
		t.val[0]=res;
		cvSet2D(img1,i,j,t);
		
	}
	
	for(int b=0; b<256; b++){
			cout<<"le pixel: "<<b<<" est repeter "<<tab[b]<<" foix!"<<endl;
		}


	return img1;
}


int main(int argc, char *argv[])
{
	//matrice 
	int size=3;
		int i,j;
	CvMat* masque    = cvCreateMat(size,size,CV_32FC1);
				
	int k=0;
	cvmSet(masque,1,1,0);
	cvmSet(masque,0,0,std::pow(2,k));k++;
	cvmSet(masque,0,1,std::pow(2,k));k++;
	cvmSet(masque,0,2,std::pow(2,k));k++;
	cvmSet(masque,1,2,std::pow(2,k));k++;
	cvmSet(masque,2,2,std::pow(2,k));k++;
	cvmSet(masque,2,1,std::pow(2,k));k++;
	cvmSet(masque,2,0,std::pow(2,k));k++;
	cvmSet(masque,1,0,std::pow(2,k));

	IplImage* img = 0; 
	img=cvLoadImage(argv[1],0);

IplImage * imagelbp = lbp(img,masque);

cvShowImage("image",img);
cvShowImage("image lbp",imagelbp);
cvWaitKey();

	return 0;
}
