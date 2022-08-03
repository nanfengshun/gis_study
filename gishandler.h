#ifndef GISHANDLER_H
#define GISHANDLER_H

#include <QWidget>
#include "gdal_priv.h"

/**
 * @brief 从dem.tif数据中读取高数据
 */

//空间位置信息
struct Location
{
    float lon;      //经度
    float lat;      //纬度
    float alt;   //海拔高度
};

class GisHandler
{
public:
    GisHandler();

private:
    int readTif();
};

#endif // GISHANDLER_H
