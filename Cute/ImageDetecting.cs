using System;

namespace Cute.Pic
{
    unsafe class ImageDetector
    {
        #region Ԥ����

        /// <summary>
        /// ͼ��ʶ��Ԥ����������
        /// </summary>
        /// <param name="Image">ͼ���׵�ַ</param>
        /// <param name="Image_W">ͼ����</param>
        /// <param name="Image_H">ͼ��߶�</param>
        /// <returns>�ı���ʾ�ַ���</returns>
        public string PreProcessing(byte* Image, int Image_W, int Image_H)
        {
            ///��ֵ������ֵ
            UInt32 sum = 0;
            int lenth = Image_W * Image_H;
            for (int i = 0; i < lenth; i++)
            {
                sum += Image[i];
            }
            byte ave = (byte)(sum / lenth);
            ///��ֵ��
            for (int i = 0; i < lenth; i++)
            {
                if (Image[i] >= ave) Image[i] = 255;
                else Image[i] = 0;
            }

            ///�ı�����ӵ�����Ϣ
            string ShowText = string.Empty;
            ShowText += string.Format("��ֵ:{0} ", ave);
            return ShowText;
        }

        #endregion

        #region ʶ��

        /// <summary>
        /// ͼ��ʶ��������
        /// </summary>
        /// <param name="Image">ͼ���׵�ַ</param>
        /// <param name="Image_W">ͼ����</param>
        /// <param name="Image_H">ͼ��߶�</param>
        /// <returns>�ı���ʾ�ַ���</returns>
        public string Detecting(byte* Image, int Image_W, int Image_H)
        {
            int[] Left_Line = new int[Image_H]; //��߽�
            int[] Right_Line = new int[Image_H]; //�ұ߽�
            int[] Mid_Line = new int[Image_H + 1]; //������ +1��Ϊ�˷���Ѱ�ҵ�һ����

            Mid_Line[Image_H] = Image_W / 2; //��ʼ����һ���е�

            ///Ѱ���ߣ�����
            for (int i = Image_H - 1; i >= 0; i--)
            {
                ///Ѱ���ұ߽�㣬ÿ�ζ�����һ���е�Ϊ��ʼ��
                int[] border = Search_Border(Image + i * Image_W, Mid_Line[i + 1], Mid_Line[i + 1], Image_W);
                Left_Line[i] = border[0];
                Right_Line[i] = border[1];
                Mid_Line[i] = (Left_Line[i] + Right_Line[i]) / 2;
            }

            ///��ʶ���ߣ�����
            for (int i = Image_H - 1; i >= 0; i--)
            {
                *(Image + i * Image_W + Left_Line[i]) = 1;
                *(Image + i * Image_W + Right_Line[i]) = 2;
                *(Image + i * Image_W + Mid_Line[i]) = 4;
            }

            ///�ı�����ӵ�����Ϣ
            string ShowText = string.Empty; 
            ShowText += string.Format("��:{0} ��:{1}\r\n", Image_W, Image_H);
            return ShowText;
        }

        /// <summary>
        /// Ѱ�߽��
        /// </summary>
        /// <param name="ImageRow">ͼ�����׵�ַ</param>
        /// <param name="LPoint">Ѱ��߽���ʼ��</param>
        /// <param name="RPoint">Ѱ�ұ߽���ʼ��</param>
        /// <param name="Width">ͼ����</param>
        /// <returns>���ұ߽��</returns>
        public unsafe int[] Search_Border(byte* ImageRow, int LPoint, int RPoint, int Width)
        {
            int[] result = new int[2]; //�߽������
            int j;

            ///��߽�
            for (j = LPoint; j > 0; j--)//��LPoint����������߽�
            {
                if (*(ImageRow + j + 1) != 0 && *(ImageRow + j) != 0 && *(ImageRow + j - 1) == 0)//����һ�ڼ����߽�
                {
                    result[0] = j;
                    break;
                }
            }
            if (j == 0) //δ��Ѱ���߽��
            {
                result[0] = 0;
            }

            ///�ұ߽�
            for (j = RPoint; j < Width - 1; j++)//��RPoint���������ұ߽�
            {
                if (*(ImageRow + j - 1) != 0 && *(ImageRow + j) != 0 && *(ImageRow + j + 1) == 0) //����һ�ڼ���ұ߽�
                {
                    result[1] = j;
                    break;
                }
            }
            if (j == Width - 1) //δ��Ѱ���߽��
            {
                result[1] = Width - 1;
            }
            return result;
        }
        #endregion
    }
}
