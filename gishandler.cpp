#pragma execution_character_set("utf-8")

#include "gishandler.h"
#include <QDebug>
#include <QTime>

GisHandler::GisHandler()
{
    readTif();
}


int GisHandler::readTif()
{
    int start = QTime::currentTime().msecsSinceStartOfDay();
    const char* path = "E:/dev/apache-tomcat-10.0.23/webapps/ROOT/terrian/ASTGTM2_N39E115_dem.tif";

    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");	// 支持中文路径
    // 注册所有功能
    GDALAllRegister();

    GDALDataset *poDataset;   //GDAL数据集

    poDataset = (GDALDataset *)GDALOpen(path, GA_ReadOnly);

    if(poDataset == NULL) {
        qDebug() << "fail in open files!!!";
        return 0;
    }

    //获取图像的尺寸
    int w = poDataset->GetRasterXSize();
    int h = poDataset->GetRasterYSize();

    //获取坐标变换系数
    double trans[6];
    poDataset->GetGeoTransform(trans);
    qDebug() << "坐标变换系数: " << trans[0] << trans[1] << trans[2] << trans[3] << trans[4] << trans[5];

    // 获取波段数:DEM为1个波段
    int bandcount = poDataset->GetRasterCount();
    //获取图像波段
    GDALRasterBand *poBand = poDataset->GetRasterBand(bandcount);

    qDebug() << "波段数: " << bandcount;
    //DEM数据为单波段数据 该代码只适用于单通道数据读取和写
    float* altArray = new float[w*h];

    QList<Location> locationList;

    GDALRasterIO(poBand, GF_Read, 0, 0, w, h, altArray, w, h, GDT_Float32, 0, 0);
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            float lon = trans[0] + i*trans[1] + j*trans[2];
            float lat = trans[3] + i*trans[4] + j*trans[5];
            float alt = altArray[i*h+j];
            Location location;
            location.lon = lon;
            location.lat = lat;
            location.alt = alt;
//            qDebug() << lon << lat << alt;
            locationList.append(location);
        }
    }

    int end = QTime::currentTime().msecsSinceStartOfDay();
    qDebug() << "cost time: " << (end-start) << ", data size: " << locationList.size();
    CPLFree(altArray);
    GDALClose(poDataset);
}
