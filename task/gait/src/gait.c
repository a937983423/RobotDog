#include "gait.h"

/*
 *功能:椭圆轨迹-对角小跑步态
 *描述：输入alpha（0~2PI），抬腿高度H，步长E，输出驱动空间theta[12]
 *输入：
    alpha：0~2PI，周期为2PI
    H：抬腿高度
    E：步长
    theta：输出驱动空间地址
 *输出：
    theta[12]:驱动空间
 *备注：
    测试值为：tort_cycloid(t, 25, 20, 50, theta, 1);
 */
int tort_cycloid(double t, double T, double H, double E, double pitch, double roll, double theta[12], int dir)
{
    double theta1[3], theta2[3], theta3[3], theta4[3];
    double theta1_s[3], theta2_s[3], theta3_s[3], theta4_s[3];
    double x, y = -27, z = 0;
    double alpha;
    double max_x = 80;
    double ca, sa;
    int a = 1;
    //将周期换算到2PI
    alpha = (t / T) * 2 * PI;
    if (alpha > 2 * PI)
        return -1;
    ca = cos(alpha);
    sa = sin(alpha);
    //设置最大x坐标
    if (dir == 1)
    {
        max_x = 80;
        y = -27 - (E - 10) * ca;
    }
    else if (dir == 2)
    {
        max_x = 80;
        y = -27 + (E - 10) * ca;
    }
    else if (dir == 3)
    {
        max_x = 80;
        y = -27.0;
        a = 1;
    }
    else if (dir == 0)
    {
        max_x = 80;
        y = -27.0;
        a = -1;
    }
    _body_attitude_invkinematics(theta1_s, theta2_s, theta3_s, theta4_s, pitch, roll, 0.0, max_x);
    //椭圆方程
    x = max_x - H * sa - 5;
    z = a * E * ca;
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta1) == -720)
        return -1;
    x = x + 5;
    z = z - 15;
    if (_one_leg_invkinematics_1(x, y, z, theta4) == -720)
        return -1;
    //腿1,4和腿2,3有半个周期差
    x = max_x - H * (-sa) - 5;
    z = a * E * (-ca);
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta2) == -720)
        return -1;
    x = x + 5;
    z = z - 15;
    if (_one_leg_invkinematics_1(x, y, z, theta3) == -720)
        return -1;
    //将关节空间转化到驱动空间
    theta[0] = _theta_0_2driver(180.0 * (theta1[2] / PI));
    theta[1] = _theta_1_2driver(180.0 * (theta2[2] / PI));
    theta[2] = _theta_2_2driver(180.0 * (theta3[2] / PI));
    theta[3] = _theta_3_2driver(180.0 * (theta4[2] / PI));
    theta[4] = _theta_4_2driver(180.0 * (theta1[1] / PI));
    theta[5] = _theta_5_2driver(180.0 * (theta2[1] / PI));
    theta[6] = _theta_6_2driver(180.0 * (theta3[1] / PI));
    theta[7] = _theta_7_2driver(180.0 * (theta4[1] / PI));
    theta[8] = _theta_8_2driver(180.0 * (theta1[0] / PI));
    theta[9] = _theta_9_2driver(180.0 * (theta2[0] / PI));
    theta[10] = _theta_10_2driver(180.0 * (theta3[0] / PI));
    theta[11] = _theta_11_2driver(180.0 * (theta4[0] / PI));
    if (theta[0] == -720 || theta[1] == -720 || theta[2] == -720 || theta[3] == -720 || theta[4] == -720 || theta[5] == -720 || theta[6] == -720 || theta[7] == -720 || theta[8] == -720 || theta[9] == -720 || theta[10] == -720 || theta[11] == -720)
        return -2;
    return 0;
}

/*
 *功能:椭圆轨迹-walk步态
 *描述：输入alpha（0~2PI），抬腿高度H，步长E，输出驱动空间theta[12]
 *输入：
    alpha：0~2PI，周期为2PI
    H：抬腿高度
    E：步长
    theta：输出驱动空间地址
 *输出：
    theta[12]:驱动空间
 *备注：
    测试值为：tort_cycloid(t, 25, 20, 50, theta, 1);
 */
int walk_cycloid(double t, double T, double H, double E, double pitch, double roll, double theta[12], int dir)
{
    double theta1[3], theta2[3], theta3[3], theta4[3];
    double theta1_s[3], theta2_s[3], theta3_s[3], theta4_s[3];
    double x, y = -27, z = 0;
    double alpha;
    double max_x = 80;
    double ca, sa, ca_4, sa_4;
    int a = 1;
    //将周期换算到2PI
    alpha = (t / T) * 2 * PI;
    if (alpha > 2 * PI)
        return -1;
    ca = cos(alpha);
    sa = sin(alpha);
    ca_4 = cos(alpha + PI / 4);
    sa_4 = sin(alpha + PI / 4);
    //设置最大x坐标
    if (dir == 1)
    {
        max_x = 80;
        y = -27 - (E - 10) * ca;
    }
    else if (dir == 2)
    {
        max_x = 80;
        y = -27 + (E - 10) * ca;
    }
    else if (dir == 3)
    {
        max_x = 80;
        y = -27.0;
        a = 1;
    }
    else if (dir == 0)
    {
        max_x = 80;
        y = -27.0;
        a = -1;
    }
    //椭圆方程
    x = max_x - H * sa;
    z = a * E * ca;
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta1) == -720)
        return -1;
    x = max_x - H * sa_4;
    z = a * E * ca_4;
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta4) == -720)
        return -1;
    x = max_x - H * (ca);
    z = a * E * (-sa);
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta2) == -720)
        return -1;
    x = max_x - H * ca_4;
    z = a * E * (-sa_4);
    if (x > max_x)
    {
        x = max_x;
    }
    if (_one_leg_invkinematics_1(x, y, z, theta3) == -720)
        return -1;
    //将关节空间转化到驱动空间
    theta[0] = _theta_0_2driver(180.0 * (theta1[2] / PI));
    theta[1] = _theta_1_2driver(180.0 * (theta2[2] / PI));
    theta[2] = _theta_2_2driver(180.0 * (theta3[2] / PI));
    theta[3] = _theta_3_2driver(180.0 * (theta4[2] / PI));
    theta[4] = _theta_4_2driver(180.0 * (theta1[1] / PI));
    theta[5] = _theta_5_2driver(180.0 * (theta2[1] / PI));
    theta[6] = _theta_6_2driver(180.0 * (theta3[1] / PI));
    theta[7] = _theta_7_2driver(180.0 * (theta4[1] / PI));
    theta[8] = _theta_8_2driver(180.0 * (theta1[0] / PI));
    theta[9] = _theta_9_2driver(180.0 * (theta2[0] / PI));
    theta[10] = _theta_10_2driver(180.0 * (theta3[0] / PI));
    theta[11] = _theta_11_2driver(180.0 * (theta4[0] / PI));
    if (theta[0] == -720 || theta[1] == -720 || theta[2] == -720 || theta[3] == -720 || theta[4] == -720 || theta[5] == -720 || theta[6] == -720 || theta[7] == -720 || theta[8] == -720 || theta[9] == -720 || theta[10] == -720 || theta[11] == -720)
        return -2;
    return 0;
}

/*
 *功能：顾名思义
 */
int fuck_earth(double t, double T, double H, double E, double theta[12])
{
    double theta1[3], theta2[3], theta3[3], theta4[3];
    double x, z;
    double alpha;

    alpha = (t / T) * 2 * PI;

    if (alpha > 2 * PI)
        return -1;

    z = E * cos(alpha);
    x = 98 - H * sin(alpha);

    if (_one_leg_invkinematics_1(x, -27, z, theta3) == -720)
        return -1;
    theta4[0] = theta3[0];
    theta4[1] = theta3[1];
    theta4[2] = theta3[2];

    //alpha = alpha + PI;
    z = E * cos(alpha);
    x = 98 - H * sin(alpha);
    if (_one_leg_invkinematics_1(x, -27, z, theta1) == -720)
        return -1;
    theta2[0] = theta1[0];
    theta2[1] = theta1[1];
    theta2[2] = theta1[2];

    theta[0] = _theta_0_2driver(180.0 * (theta1[2] / PI));
    theta[1] = _theta_1_2driver(180.0 * (theta2[2] / PI));
    theta[2] = _theta_2_2driver(180.0 * (theta3[2] / PI));
    theta[3] = _theta_3_2driver(180.0 * (theta4[2] / PI));
    theta[4] = _theta_4_2driver(180.0 * (theta1[1] / PI) - 15);
    theta[5] = _theta_5_2driver(180.0 * (theta2[1] / PI) - 15);
    theta[6] = _theta_6_2driver(180.0 * (theta3[1] / PI) - 15);
    theta[7] = _theta_7_2driver(180.0 * (theta4[1] / PI) - 15);
    theta[8] = _theta_8_2driver(180.0 * (theta1[0] / PI));
    theta[9] = _theta_9_2driver(180.0 * (theta2[0] / PI));
    theta[10] = _theta_10_2driver(180.0 * (theta3[0] / PI));
    theta[11] = _theta_11_2driver(180.0 * (theta4[0] / PI));
    if (theta[0] == -720 || theta[1] == -720 || theta[2] == -720 || theta[3] == -720 || theta[4] == -720 || theta[5] == -720 || theta[6] == -720 || theta[7] == -720 || theta[8] == -720 || theta[9] == -720 || theta[10] == -720 || theta[11] == -720)
        return -2;
    return 0;
}

/*
 *功能：站立
 *输入：
    pitch,roll,yaw:欧拉角
    theta：驱动空间数据的地址
 *输出：
    theta：驱动空间
 *返回值：成功返回0
    
 */
int stand(double pitch, double roll, double yaw, double theta[12])
{
    double theta1[3], theta2[3], theta3[3], theta4[3];

    if (_body_attitude_invkinematics(theta1, theta2, theta3, theta4, pitch, roll, yaw, 80))
        return -1;
    //将关节空间转化到驱动空间
    theta[0] = _theta_0_2driver(180.0 * (theta1[2] / PI));
    theta[1] = _theta_1_2driver(180.0 * (theta2[2] / PI));
    theta[2] = _theta_2_2driver(180.0 * (theta3[2] / PI));
    theta[3] = _theta_3_2driver(180.0 * (theta4[2] / PI));
    theta[4] = _theta_4_2driver(180.0 * (theta1[1] / PI));
    theta[5] = _theta_5_2driver(180.0 * (theta2[1] / PI));
    theta[6] = _theta_6_2driver(180.0 * (theta3[1] / PI));
    theta[7] = _theta_7_2driver(180.0 * (theta4[1] / PI));
    theta[8] = _theta_8_2driver(180.0 * (theta1[0] / PI));
    theta[9] = _theta_9_2driver(180.0 * (theta2[0] / PI));
    theta[10] = _theta_10_2driver(180.0 * (theta3[0] / PI));
    theta[11] = _theta_11_2driver(180.0 * (theta4[0] / PI));
    if (theta[0] == -720 || theta[1] == -720 || theta[2] == -720 || theta[3] == -720 || theta[4] == -720 || theta[5] == -720 || theta[6] == -720 || theta[7] == -720 || theta[8] == -720 || theta[9] == -720 || theta[10] == -720 || theta[11] == -720)
        return -2;
    return 0;
}
