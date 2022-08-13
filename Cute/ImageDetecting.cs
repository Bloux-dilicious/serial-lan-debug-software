using System;

namespace Cute.Pic
{
    unsafe class ImageDetector
    {
        #region 预处理

        /// <summary>
        /// 图像识别预处理主函数
        /// </summary>
        /// <param name="Image">图像首地址</param>
        /// <param name="Image_W">图像宽度</param>
        /// <param name="Image_H">图像高度</param>
        /// <returns>文本显示字符串</returns>
        public string PreProcessing(byte* Image, int Image_W, int Image_H)
        {
            ///均值法求阈值
            UInt32 sum = 0;
            int lenth = Image_W * Image_H;
            for (int i = 0; i < lenth; i++)
            {
                sum += Image[i];
            }
            byte ave = (byte)(sum / lenth);
            ///二值化
            for (int i = 0; i < lenth; i++)
            {
                if (Image[i] >= ave) Image[i] = 255;
                else Image[i] = 0;
            }

            ///文本框添加调试信息
            string ShowText = string.Empty;
            ShowText += string.Format("阈值:{0} ", ave);
            return ShowText;
        }

        #endregion

        #region 识别

        /// <summary>
        /// 图像识别主函数
        /// </summary>
        /// <param name="Image">图像首地址</param>
        /// <param name="Image_W">图像宽度</param>
        /// <param name="Image_H">图像高度</param>
        /// <returns>文本显示字符串</returns>
        public string Detecting(byte* Image, int Image_W, int Image_H)
        {
            int[] Left_Line = new int[Image_H]; //左边界
            int[] Right_Line = new int[Image_H]; //右边界
            int[] Mid_Line = new int[Image_H + 1]; //中心线 +1是为了方便寻找第一个点

            Mid_Line[Image_H] = Image_W / 2; //初始化第一个中点

            ///寻边线，中线
            for (int i = Image_H - 1; i >= 0; i--)
            {
                ///寻左右边界点，每次都以上一行中点为起始点
                int[] border = Search_Border(Image + i * Image_W, Mid_Line[i + 1], Mid_Line[i + 1], Image_W);
                Left_Line[i] = border[0];
                Right_Line[i] = border[1];
                Mid_Line[i] = (Left_Line[i] + Right_Line[i]) / 2;
            }

            ///标识边线，中线
            for (int i = Image_H - 1; i >= 0; i--)
            {
                *(Image + i * Image_W + Left_Line[i]) = 1;
                *(Image + i * Image_W + Right_Line[i]) = 2;
                *(Image + i * Image_W + Mid_Line[i]) = 4;
            }

            ///文本框添加调试信息
            string ShowText = string.Empty; 
            ShowText += string.Format("宽:{0} 高:{1}\r\n", Image_W, Image_H);
            return ShowText;
        }

        /// <summary>
        /// 寻边界点
        /// </summary>
        /// <param name="ImageRow">图像行首地址</param>
        /// <param name="LPoint">寻左边界起始点</param>
        /// <param name="RPoint">寻右边界起始点</param>
        /// <param name="Width">图像宽度</param>
        /// <returns>左右边界点</returns>
        public unsafe int[] Search_Border(byte* ImageRow, int LPoint, int RPoint, int Width)
        {
            int[] result = new int[2]; //边界点数组
            int j;

            ///左边界
            for (j = LPoint; j > 0; j--)//从LPoint处向左找左边界
            {
                if (*(ImageRow + j + 1) != 0 && *(ImageRow + j) != 0 && *(ImageRow + j - 1) == 0)//两白一黑检测左边界
                {
                    result[0] = j;
                    break;
                }
            }
            if (j == 0) //未找寻到边界点
            {
                result[0] = 0;
            }

            ///右边界
            for (j = RPoint; j < Width - 1; j++)//从RPoint处向右找右边界
            {
                if (*(ImageRow + j - 1) != 0 && *(ImageRow + j) != 0 && *(ImageRow + j + 1) == 0) //两白一黑检测右边界
                {
                    result[1] = j;
                    break;
                }
            }
            if (j == Width - 1) //未找寻到边界点
            {
                result[1] = Width - 1;
            }
            return result;
        }
        #endregion
    }
}
