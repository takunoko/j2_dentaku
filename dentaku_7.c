//電卓成プログラム
#include <stdio.h>
#include <math.h>

#define cls(x,y)	((x) = 0, (y) = 0)



//文字列の読み込み
void read_mojiretu(char mojiretu[]){
	printf(" # ");
	scanf("%s",mojiretu);
}

//計算
double keisan(double kazu[], int hugou[]){
	int num, hugou_i;
	cls(num,hugou_i);
	int num2 = 0;

	//累乗
	while(hugou[num++]){
		num2 = num;
		while (hugou[num2-1] == 5) {
			switch (hugou[num-1]){
				case 5 : kazu[num-1] = pow(kazu[num-1], kazu[num]); break;
				default : break;
			}
			num2++;
		}
	}
	cls(num,hugou_i);
	//積商
	while(hugou[num++]){
		num2 = num;
		while (hugou[num2-1] == 3 || hugou[num2-1] == 4 || hugou[num2-1] == 5) {
			if (hugou[num2-1] == 5) {
				num2++;
			}
			switch (hugou[num2-1]){
				case 3 : kazu[num-1] = (kazu[num-1] * kazu[num2]); break;
				case 4 : kazu[num-1] = (kazu[num-1] / kazu[num2]); break;
				default : break;
			}
			num2++;
		}
	}
	cls(num,hugou_i);
	//和差
	while(kazu[num++]){
		switch (hugou[num-1]){
			case 1 : kazu[0] = (kazu[0] + kazu[num]); break;
			case 2 : kazu[0] = (kazu[0] - kazu[num]); break;
			default : break;
		}
	}
	
	return kazu[0];
}

//正負
int check_seihu(char mojiretu[],double kazu[], int num, int *mainasu, int moji_i){
	if (mojiretu[moji_i] == '(' && mojiretu[moji_i+1] == '-') {
		*mainasu = -1;
		moji_i += 2;
	}
	return moji_i;
}
//演算子の読み取り
int check_hugou(char mojiretu[], int hugou[],int moji_i, int hugou_i){
	// +:1 -:2 *:3 /:4 ^:5
	if(mojiretu[moji_i] == '+'){
		hugou[hugou_i] = 1; hugou_i++;
	}else if(mojiretu[moji_i] == '-'){
		hugou[hugou_i] = 2; hugou_i++;
	}else if(mojiretu[moji_i] == '*'){
		hugou[hugou_i] = 3; hugou_i++;
	}else if(mojiretu[moji_i] == '/'){
		hugou[hugou_i] = 4; hugou_i++;
	}else if(mojiretu[moji_i] == '^'){
		hugou[hugou_i] = 5; hugou_i++;
	}
	return (hugou_i);
}
//小数
int check_syousuu(char mojiretu[], double kazu[], int num, int moji_i){
	int syou;
	syou = 1;
	if (mojiretu[moji_i] == '.') {
		moji_i++;
		while(mojiretu[moji_i] <= '9' && mojiretu[moji_i] >= '0'){
			kazu[num] = kazu[num] + (mojiretu[moji_i] - '0') * pow( 10, -(syou));
			syou++;
			moji_i++;
		}
	}
	return moji_i;
}
//整数
int check_seisuu(char mojiretu[], double kazu[], int num, int moji_i){
	while(mojiretu[moji_i] <= '9' && mojiretu[moji_i] >= '0'){
		kazu[num] = kazu[num]*10 + (mojiretu[moji_i++] - '0');
	}
	return moji_i;
}

void check_mojiretu(char mojiretu[]){
	int moji_i = 0, num = 0;
	double kekka;
	double kazu[100] = {0};
	int hugou[100] = {0};
	int mainasu = 1;
	int hugou_i = 0;

	//文字列を数字と記号に分ける
	for ( moji_i = 0; mojiretu[moji_i] != '\0'; moji_i++, mainasu = 1){
		if(mojiretu[moji_i] <= '9' && mojiretu[moji_i] >= '0' ||
				mojiretu[moji_i] == '(' || mojiretu[moji_i] == '.'){
			//正負読み込み
			moji_i = check_seihu(mojiretu, kazu, num, &mainasu ,moji_i);
			//整数読み込み
			moji_i = check_seisuu(mojiretu, kazu, num, moji_i);
			//小数点以下読み込み
			moji_i = check_syousuu(mojiretu, kazu, num, moji_i);

			kazu[num] *= mainasu;
			num++;
		}
		hugou_i = check_hugou(mojiretu, hugou, moji_i, hugou_i);
	}
	//計算
	printf("→ %g\n",keisan(kazu, hugou));
}

int main(void){
	char mojiretu[100];
	int i;

	while (1){
		read_mojiretu(mojiretu);
		check_mojiretu(mojiretu);
		for (i = 0; i < 100; i++)
			mojiretu[i] = '\0';
	}
	return 0;
}
