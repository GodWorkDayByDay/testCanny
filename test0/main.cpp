//#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\gpu\gpu.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Windows.h>
#include <opencv2\core\cuda_devptrs.hpp>
using namespace cv;
using namespace std;
using namespace cv::gpu;
int main()
{
	double cost1, cost2;
	DWORD startTime, endTime;
	string inputfile;
	cout << "������ͼƬ��ţ�";
	cin >> inputfile;
	Mat srcImage = imread(inputfile+".jpg");     //Ĭ��.jpg��׺
	imshow("��ԭʼ�� canny��Ե���", srcImage);
	Mat dstImage,edge, grayImage,temp;
	
	gpu::GpuMat eg, gray;	
	dstImage.create(srcImage.size(), srcImage.type());
	
    //ԭͼת���ɻҶ�ͼ��
	cvtColor(srcImage, grayImage, CV_BGR2GRAY); 
	//�ϴ��Ҷ�ͼ
    gray.upload(grayImage);
	//��ͼ���봦��
	blur(grayImage, edge, Size(3, 3));

	//ִ��canny����
	startTime = GetTickCount();   //��¼�������ʼʱ��
	for (int i = 0; i < 100;i++)  //ͼƬ�ļ�̫С��ʱ����ϣ��ļ��㹻����ע�͵�����
	Canny(edge, edge, 3, 9, 3);
	endTime = GetTickCount();      //��¼����Ľ���ʱ��
	imshow("��Ч��ͼ�� canny", edge);
	cost1 = endTime - startTime;
	cout << "��������ʱ��Ϊ��" << cost1<<"ms"<<endl;


	/*����Ϊ����GPU���٣�������ͬ�Ĵ�������*/
	//���봦��
	gpu::blur(gray, eg, Size(3, 3));
	startTime = GetTickCount();   //��¼�������ʼʱ��
	for (int i = 0; i < 100; i++)          //ͼƬ�ļ�̫С��ʱ����ϣ��ļ��㹻����ע�͵�����
	gpu::Canny(eg, eg, 3, 9, 3);
	endTime = GetTickCount();      //��¼����Ľ���ʱ��
	eg.download(temp);             //������GPU�������ͼƬ����ʾ
	imshow("��Ч��ͼ�� GPU����", temp);
	cost2 = endTime - startTime;
	cout << "gpu���ٴ���ʱ��Ϊ��" << cost2 << "ms" << endl;
	cout << "���ٱȣ�" << (cost1 - cost2) / cost1 << endl;

	waitKey(0);
	return 0;
}

