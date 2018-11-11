#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<corecrt_math_defines.h>
#include<string.h>

int main() {

	double MAX[2] = { 0, 0 }, MIN[2] = { 0, 0 }, DAT[2] = {0,0}, START[2] = { 0, 0 }, END[2] = { 0, 0 };
	int lines = 3;//�����f�[�^�i�[�s��3�s�ڂȂ���

	//char str1[24] = "./Ryo.05-35_1-2_B-V_";
	char str1[24] = "./dats/";
	//char str2[24] = "\0";
	char str2[24] = "Ryo.05-35_1-2_B-V_"; // Ryo.05-35_1-2_B-V_ ������i�t�@�C���̋��ʖ�����������j
	char str3[10][24] = { '\0' }; //0.35mA �� 0.35mA_R ������i���l�����j
	char str4[24] = ".dat";

	printf("�t�@�C���擪���̋��ʖ���������͂��Ă�������(First name):");
	scanf_s("%s", str2, 24);

	printf("�t�@�C���㔼���̐��l��������͂��Ă�������(Last name)  �� .dat �͊܂܂Ȃ��@��:0.35mA\n");
	printf("���P�ʍ��� 0.35mA_R �Ȃǂ���, �ő�10�܂�(�Ԃ͋󔒂������āC10�����̎��͑���� 0 ����͂��Ă�������)\n");
	scanf_s("%s %s %s %s %s %s %s %s %s %s", str3[0], 24, str3[1], 24, str3[2], 24, str3[3], 24, str3[4], 24, str3[5], 24, str3[6], 24, str3[7], 24, str3[8], 24, str3[9], 24);

	for (int i = 0; i < 10;i++) {
		char filename[64] = { '\0' }, filename_CSV[64] = { '\0' };
		//txt�t�@�C���p�̖��O�쐬
		strcat(filename, str1);
		strcat(filename, str2);
		strcat(filename, str3[i]);
		strcat(filename, str4);

		//csv�t�@�C���p�̖��O�쐬
		strcat(filename_CSV, str2);
		strcat(filename_CSV, str3[i]);

		//data�t�@�C���̓ǂݍ���
		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			fprintf(stderr, "cannat open %s\n", filename);
			exit(EXIT_FAILURE);
		}

		char dum[100];
		fscanf(fp, "%*96c", dum); //�s�v�s�폜����

		//3�s�ڂ������l�Ƃ���
		fscanf(fp, "	%lf	%lf", &DAT[0], &DAT[1]);

		MAX[0] = lines;
		MAX[1] = DAT[0];
		MIN[0] = lines;
		MIN[1] = DAT[0];

		START[0] = lines;


		//������while���ɗ����4�s�ڂ��猩�n�߂邱�ƂɂȂ�
		lines++;
		while (fscanf(fp, "	%lf	%lf", &DAT[0], &DAT[1]) != EOF) {

			if (DAT[0] >= MAX[1]) {
				MAX[0] = lines;
				MAX[1] = DAT[0]; //DAT[0]��x�����̒l�Ȃ̂Œ���
			}

			if (DAT[0] <= MIN[1]) {
				MIN[0] = lines;
				MIN[1] = DAT[0]; //DAT[0]��x�����̒l�Ȃ̂Œ���
			}
			END[0] = lines;
			lines++;
		}

		fclose(fp);

		//�t�@�C���֌��ʂ������o��
		FILE *output_BV,*CSV_BV;
		output_BV = fopen("output_B-V.txt", "a");
		CSV_BV = fopen("CSV_BV.csv", "a");
		fprintf(output_BV, "%s                                   | MAX : %4d , MIN : %4d , TotalLines : %d\n", str3[i], (int)MAX[0], (int)MIN[0], (int)END[0]);

		if (MAX[0] < MIN[0]) {
			//START�ʒu�̓K����
			if (fabs(MIN[0] - MAX[0]) < fabs(MAX[0] - START[0])) {
				START[0] = MAX[0] - fabs(MIN[0] - MAX[0]);
			}

			//END�ʒu�̓K����
			if (fabs(MIN[0] - MAX[0]) < fabs(END[0] - MIN[0])) {
				END[0] = MIN[0]+ fabs(MIN[0] - MAX[0]);
			}

			//txt�t�@�C���ɏ����o��
			fprintf(output_BV, "RED (+ -> -) : %4d -> %4d\n", (int)MAX[0], (int)MIN[0]);
			fprintf(output_BV, "BLUE(- -> +) : %4d -> %4d\n", (int)START[0], (int)MAX[0]);
			fprintf(output_BV, "BLUE(- -> +) : %4d -> %4d(end)\n", (int)MIN[0], (int)END[0]);

			//csv�t�@�C���ɏ����o��
			fprintf(CSV_BV, "%s,%4d,%4d,RED\n", filename_CSV,(int)MAX[0], (int)MIN[0]);
			fprintf(CSV_BV, "%s,%4d,%4d,BLUE\n", filename_CSV, (int)START[0], (int)MAX[0]);
			fprintf(CSV_BV, "%s,%4d,%4d,BLUE\n", filename_CSV, (int)MIN[0], (int)END[0]);
		}
		else if (MIN[0] < MAX[0]) {
			//START�ʒu�̓K����
			if (fabs(MAX[0] - MIN[0]) < fabs(MIN[0] - START[0])) {
				START[0] = MIN[0] - fabs(MAX[0] - MIN[0]);
			}

			//END�ʒu�̓K����
			if (fabs(MAX[0] - MIN[0]) < fabs(END[0] - MAX[0])) {
				END[0] = MAX[0] + fabs(MAX[0] - MIN[0]);
			}

			//txt�t�@�C���ɏ����o��
			fprintf(output_BV, "BLUE(- -> +) : %4d -> %4d\n", (int)MIN[0], (int)MAX[0]);
			fprintf(output_BV, "RED (+ -> -) : %4d -> %4d\n", (int)START[0], (int)MIN[0]);
			fprintf(output_BV, "RED (+ -> -) : %4d -> %4d(end)\n", (int)MAX[0], (int)END[0]);
		
			//csv�t�@�C���ɏ����o��
			fprintf(CSV_BV, "%s,%4d,%4d,BLUE\n", filename_CSV, (int)MIN[0], (int)MAX[0]);
			fprintf(CSV_BV, "%s,%4d,%4d,RED\n", filename_CSV, (int)START[0], (int)MIN[0]);
			fprintf(CSV_BV, "%s,%4d,%4d,RED\n", filename_CSV, (int)MAX[0], (int)END[0]);
		}
		fprintf(output_BV, "\n");
		fclose(output_BV);
		fclose(CSV_BV);

		lines = 3; //���̃t�@�C���𑱂��ď������邽�߂ɂ����ŏ���������
	}

	/*
data sample

Sample no: ,   T=(K),   L(um)�~w(um)=�~,   N=
					Vosc (mV)             Iosc(mA)
	400859.885000	498.550694
	400091.465000	500.886003
	399356.090000	505.048666
	398873.606000	507.989167
	398150.566000	511.297015
	397346.637000	511.096082
	396592.043000	510.451856
	395834.294000	510.715981
	395096.394000	509.732093
	394140.988000	510.349422
	393664.973000	511.449376
	392720.105000	514.836486
	391990.509000	514.865289
	391497.073000	515.570968
	390498.102000	514.595659
	389989.502000	511.231804
	388954.311000	512.567753
	388221.156000	513.622825
	387748.960000	512.773395
	386796.920000	513.267919
	386541.410000	511.327857
	385279.373000	510.557293

*/

}