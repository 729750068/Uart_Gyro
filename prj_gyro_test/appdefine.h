#ifndef APPDEFINE_H
#define APPDEFINE_H
#include "stdint.h"
#include "qglobal.h"
#include <qmetatype.h>

#define             Neutral_Version_En      0
#define             FCW_ID_Buf_MaxSize      20
#define             TARGET_MAX_NUM          128

#define             CALC_ECS(SNR,RANGE)     (SNR + 8 * log10(RANGE))
#define             MaxRCS_Human            18 // 10以内
#define             MaxRCS_Animal           22
#define             MaxRCS_Vehicle          100
#define             UpgardeToolPath         "Upgrade_Tool_V1.1.2.exe"
#define             ClassificationEn        0 //目标分类 -1打开 0关闭 再目标表列表上体现
#define             RadarMODE               12 // //1FCW /2三车道 /3正常模式

//#define             TARGET_MAX_NUM2         64
#define             DDebug_Enable           1
#define             Angle_weight_Size       20

#define             TexT_Target_info        0

#define             CTRadarVideo_en         1

//#define             Load_Line_Number        3
//#define             Load_Line_Start         2 * Load_Line_Number
#define             Load_Max_Number         20
#define             RangeLine_Max_Number    2
#define             NoMove_Min_Speed        0.3

#define             System_TimeShow_enable  1
#define             Target_List_show_enable 1
#define             SaveTargetFile          1
#define             TargetAngle_Treatment_enable    1
#define             TargetAngle_Treatment_Buffer    TDisTTargetInfoFrame
#define             Angle_Treatment_BufferSize      Angle_weight_Size

//BUS
#define             BUS_TYPE_ENET           "ENET"
#define             BUS_TYPE_ENET_Index     0
#define             BUS_TYPE_CAN            "CAN"
#define             BUS_TYPE_CAN_Index      1

#if DDebug_Enable
    #define DDebug  //
#else
    #define DDebug  qDebug()
#endif

#define             AXIS_NUMBER             2
#define             Axis1                   0
#define             Axis2                   1

//CAN 300 VA
#define CAN_START_TEST        0XC5C50000
#define CAN_STOP_TEST         0XC5C50001
#define CAN_GET_CFG           0XC5C50002
#define CAN_SET_CFG           0XC5C50003
#define CAN_BURN_CFG          0XC5C50004
#define CAN_SET_KAL_E         0xC5C50005
#define UPGRADE_FIRMWARE_CODE 0XC5C55A5A

#define CMD_ID 0x521

//start with
#define     RUNTST_ACK                      "FT "
#define     STPTST_ACK                      "stopping test"
#define     CFGRHEX_ACK                     "cfgrhex"
#define     CFGSHEX_ACK                     "Transfer"
#define     CFGBURN_ACK                     "Configuration successfully saved"
#define     BBREGR_ACK                      "Value of 0x"
#define     BBREGW_ACK                      "bbregw 0x"

union STATUS_WORD1 {
    struct {
        uint32_t	RSV:			16;
        uint32_t	UPDATE_RATE:	5;	//0 - 32 /s, 0: update only one time per command
        uint32_t	SENSOR_FAIL:	1;	//1: Fail, 0: NOR
        uint32_t	OUT_MODE:		1;	//1: Filtered, 0: RAW
        uint32_t	TEMP_OV:		1; 	//temperature over range 1: OV, 0: NOR
        uint32_t	TEMP: 			8;	//-128 to 127 degrees,
    } BF;
    uint32_t WORDVAL;
} ;

union STATUS_WORD2 {
    struct {
        uint32_t	RSV:			5;
        uint32_t	FRAME_NUM: 		27;	//Frame number of current run
    } BF;
    uint32_t WORDVAL;
};

union DATA_WORD1{
    struct {
        uint32_t	RSV:			3;
        uint32_t	TRK_STATUS:		3;
        int     	VEL:			14; //- 81.92 to 81.91 m/s, x0.01, +: away from sensor
        uint32_t	RANGE: 			12;	//0 - 409.5m, x0.1
    } BF;
    uint32_t WORDVAL;
};

union DATA_WORD2{
    struct {
        uint32_t	RSV:			3;
        uint32_t	SNR:			9;	//0 to 51.1	dB,	x0.1
        int     	ACC:			10;	//-25.60 to 25.55 m/(s^2), x0.05, +: away from sensor
        int     	ANGLE: 			10;	//-51.2 to 51.1 degrees, x0.1, 0: front, +: counter-clockwise
    } BF;
    uint32_t WORDVAL;
};

//CAN 200
//通信总线类型
#define             BusMode_NULL            0
#define             BusMode_UART            1
#define             BusMode_CAN             2
#define             BusMode_ENET            3
//Data 数据模式
#define             DataMode_NULL               -1
#define             DataMode_RawTarget          0
#define             DataMode_TrackTarget        1
#define             DataMode_RawTrackTarget     2
#define             DataMode_RawData            3
//雷达类型
#define             Radar_NULL              "NULL"
#define             Radar_CTLRR100          "CTLRR-100"
#define             Radar_CTLRR200VA        "CTLRR-200-V1"
#define             Radar_CTLRR200VB        "CTLRR-200-V2"
#define             Radar_CTLRR300VA        "CTLRR-300-V1"
#define             Radar_CTLRR300VB        "CTLRR-300-V2"
#define             Radar_CTLRR300VB_1      "CTLRR-300-V2_1"
#define             Radar_CTLRR300CDEMO     "CTLRR-300-CDEMO"
//TX模式
#define             Tx_Mode_NULL            -1
#define             Tx_Mode_TX1             0
#define             Tx_Mode_TX2             1
#define             Tx_Mode_TX1TX2          2

//滑窗轨迹buffer size
#define             TTrajectoryBufferSize       50
#define             tDataType                   double
typedef struct tagTargetInfo{
public:
    int     ID;
    tDataType distance = 0; //单位m -100表示无效
    tDataType speed = 0;// 单位m/s -100表示无效
    tDataType angle = 0;//单位deg -100表示无效
    tDataType power = 0;
    tDataType SNR = 0;
    tDataType RCS = 0;
    tDataType KState = 0;  //-1表示无效
    tDataType Amp = 0;   //-100表示无效
    tDataType X_Lateral = 0; //横向距离 也就是 X
    tDataType Y_Longitudinal = 0 ;//纵向距离 也就是Y
    tDataType Xaccel = 0;    //X方向加速度
    tDataType Yaccel = 0;    //X方向加速度
    bool    IsPalisade  = false;    //栅栏
    bool    IsPerson    = false;    //人
    bool    IsStationary    = false ;//静止的
    bool    IsCome          = false; //来向的
    bool    IsAway_From     = false; //远离的
    bool ValidFlag = false;
    bool Angle_Treatment_ValidFlag = false;
    bool IsAfterTrack       = false; //是否是跟踪之后的
    unsigned int TargetLabel = 0;     //1-fcw目标
    uint8_t TypeAttribute = 0; //目标类别属性 0 未知 1人 2动物 3车辆
    uint8_t motionAttribute = 0;//目标运动属性 0未知 1固定物体 2移动物体
}TargetInfo;


typedef struct tagTargetInfoFrame{
public:
    TargetInfo Target[TARGET_MAX_NUM];
    bool ValidFlag = false;
    bool IsTrack   = false;
    QString TimeStamp;
    QString TimeUnix;
    int FrameNumber = 0;
    int FcwID[3] ; //0-mid 1-L 2-R
    double FCWTTC = 0;
    double FCWPET = 0;
    double VehicleSpeed = 0;
    double EstimateCarSpeed = 0;
    double VehicleYawRate = 0;
    double VehicleRadiusCurvature = 0;
    int mode = 0; //1 - normal  2 FCw  3 Fcw Debug 4 FCW normal
    int TotalTarget = 0;
    QString Software_Version;
    QString Radar_Version;
    float CarYawRate = 0;
}TargetInfoFrame;

Q_DECLARE_METATYPE(TargetInfoFrame);

//200 雷达配置
#define        ESR_TRX_GAIN_PARAM         0x321
typedef union tagDUTSetTRXMsg {
    quint64 word;
    struct {
        quint64 vga1Gain    :8;
        quint64 vga2Gain    :8;
        quint64 lnaGain     :8;
        quint64 tiaGain     :16;
        quint64 txPower     :8;
        quint64 txBw        :16;
    }bit;
}TDUTSetTRXMsg;

#define         ESR_DSP_PARAM              0x322
typedef struct {
    uint8_t pingpongTx;     //是否使用双天线远近切换
    uint8_t nfRangeThrd;    //远近距离分界点，单位米
    uint8_t trackType;      //track算法类型，0 - 默认算法， 1 - 卡尔曼滤波
    uint8_t resv;
    uint8_t NuLL1;
    uint8_t NuLL2;
    uint8_t NuLL3;
    uint8_t NuLL4;
}radarDspCfg_t;

typedef struct APP_MODE{
public:
    quint8 BusMode          =   BusMode_NULL;    // 0 无效 ， 1 串口 ， 2 can  3 ENET
    quint8 Data_Mode        =   DataMode_NULL;  //数据模式
    QString RadarType       =   Radar_NULL;    // 雷达型号
    qint8   TX_Mode         =   Tx_Mode_TX1;    //天线类型
    bool    Connect_State   =   false;

}APP_MODE_t;

typedef struct Display_MODE{
public:
    bool Stationary = true;
    bool come = true ;
    bool Far_Away = true;
    bool Speed_Fliter = true;
    bool Trajectory = false;
}Display_MODE_t;


typedef struct Point
{
public:
    tDataType X[TARGET_MAX_NUM];
    tDataType Y[TARGET_MAX_NUM];

}TrajectoryPoint;

typedef struct Trajectory
{
public:
    TrajectoryPoint TTrajectoryPoint[TTrajectoryBufferSize];
    int validityCount[TARGET_MAX_NUM];   //有效值个数

}TrajectoryBuffer;
////Axis Config
//typedef struct Display_MODE{
//public:
//    int Xmax = true;
//    int Ymax = true;
//    int Xmin = true;
//    int Ymin = true;

//    int PointSize = true;
//    int laneNum = true;
//    int Ymin = true;
//}Display_MODE_t;

#endif // APPDEFINE_H
