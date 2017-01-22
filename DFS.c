#pragma config(StandardModel, "EV3_REMBOT")

/*	NIM/Nama	:		13514004/Catherine Pricilla
									13514063/Steffi Indrayani
									13514071/Sekar Anglila Hapsari
		Nama File :		MencariJodoh.c
		Topik			:		DFS dan BFS
*/

//KAMUS
	long color[3];
	int branch[20]; //Cabang
	int route[20]; //Rute yang diambil
	int jml[20]; //Menyimpan jumlah cabang
	int nr = 0; //Counter jalan yang sudah diambil
	bool passed = false;//Boolean apakah percabangan sudah dilewati
	int top = 0; int top2 = 0; int br = 0; int erase = 0;

//PROSEDUR DAN FUNGSI
bool isBlue (long red, long green, long blue) {
	if ((blue >= 90) && ((blue-red) > 50) && ((blue-green) > 50)) return true;
	else return false;
}

bool isRed (long red, long green, long blue) {
	if ((red >= 90) && ((red-blue) > 50) && ((red-green) > 50)) return true;
	else return false;
}

bool isGreen (long red, long green, long blue) {
	if ((green >= 90) && ((green-red) > 50) && ((green-blue) > 50)) return true;
	else return false;
}

void LineFollower() {
//Robot jalan mengikuti garis hitam
//Algoritma
	  	do {
	    // sensor sees light:
	    if(getColorReflected(colorSensor) < 65) {
	    	// counter-steer right:
	    	motor[leftMotor] = 15;
	    	motor[rightMotor] = 55;
	    } else {
	      // counter-steer left:
	      motor[leftMotor]  = 55;
	      motor[rightMotor] = 15;
	    }
	    SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
	    getColorRGB(colorSensor,color[0],color[1],color[2]);
	  } while(isBlue(color[0],color[1],color[2]) == false && isGreen(color[0],color[1],color[2]) == false
	  			 &&	isRed(color[0],color[1],color[2]) == false && (getColorName(colorSensor) != colorGreen) &&
	  			(getColorName(colorSensor) != colorRed) && (getColorName(colorSensor) != colorBlue));
}

void turn_right(){
//Membelokkan robot ke kanan
//Kamus Lokal
	bool black = false;

//Algoritma
	//Maju terlebih dahulu
	turnRight(50, degrees, 40);
	forward(100, milliseconds, 50);
	//Belok kanan
	while(!black){
		setMotorSpeed(leftMotor, 100);
		setMotorSpeed(rightMotor, 30);
		if(getColorReflected(colorSensor) > 65){
			black = true;
		}
	}
	passed = false;
}

void turn_right_2(){
//Membelokkan robot ke jalur kanan
//Kamus Lokal
	bool black = false;

//Algoritma
	//Atur Posisi terlebih dahulu
	backward(400, milliseconds, 50);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 0);
	wait1Msec(1500);
	forward(500, milliseconds, 50);

	//Belok ke jalur kanan
	while(!black)
	{
		setMotorSpeed(leftMotor, 30);
		setMotorSpeed(rightMotor, 100);
		if(getColorReflected(colorSensor) < 65)
		{
			black = true;
		}
	}
}

void turn_left(){
//Membelokkan robot ke kiri
//Kamus Lokal
	bool black = false;

//Algoritma
	//Atur Posisi terlebih dahulu
	turnLeft(30, degrees, 50);
	backward(400, milliseconds, 50);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 0);
	wait1Msec(1500);
	forward(500, milliseconds, 50);

	//Belok kiri
	while(!black)
	{
		setMotorSpeed(leftMotor, 30);
		setMotorSpeed(rightMotor, 100);
		if(getColorReflected(colorSensor) < 65)
		{
			black = true;
		}
	}
	passed = false;
}

void turn_left_2(){
//Membelokkan robot ke jalur kanan
//Kamus Lokal
	bool black = false;

//Algoritma
	//Atur Posisi terlebih dahulu
	backward(500, milliseconds, 50);
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 30);
	wait1Msec(1500);

	//Belok ke jalur kanan
	while(!black){
		setMotorSpeed(leftMotor, 100);
		setMotorSpeed(rightMotor, 30);
		if(getColorReflected(colorSensor) < 65)
		{
			black = true;
		}
	}
}

void turn_left_3(int cabangAwal, int cabangAkhir, int ncabang) {
	int x = 0;
	int cabang;
	bool black = false;
	bool white = false;
	if (cabangAwal < cabangAkhir) {
		cabang = cabangAkhir-cabangAwal;
	}
	else if (cabangAkhir < cabangAwal) {
		cabang = (ncabang+1)-(cabangAwal-cabangAkhir);
	}
	bool stop = false;
	turnLeft(30, degrees, 50);
	backward(400, milliseconds, 50);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 0);
	wait1Msec(1500);
	forward(500, milliseconds, 50);
	while(!stop){
		setMotorSpeed(leftMotor, 30);
		setMotorSpeed(rightMotor, 100);
		while (!black){
			if(getColorReflected(colorSensor) > 65){
				black = true; white = false; 	x++;
			}
		}
		if (x > cabang) stop = true;
		while (!white){
			if(getColorReflected(colorSensor) < 65){
				black = false; white = true;
			}
		}
	}
}

void reverse() {
//Robot berputar balik
//Algoritma
	resetGyro(gyroSensor);
	while(getGyroDegrees(gyroSensor) <= 180)
	{
		motor[rightMotor] = 0;
		motor[leftMotor] = 50;
	}
	nr--; erase = route[nr];
	route[nr] = -1; passed = true;
	if (erase == br){
		top2--; jml[top2] = -1;
		br = jml[top2 - 1]; erase = 0;
		top--; route[nr - 1] = branch[top];
		branch[top] = -1;
		LineFollower(); turn_right_2();
		LineFollower(); turn_left();
	}
}

void reverse_2() {
//Robot berputar balik
//Algoritma
	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(1000);
}

int countCabang(){
//Menghitung cabang dalam persimpangan
//Kamus Lokal
	int brx = 0;

//Algoritma
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	resetGyro(gyroSensor);
	while(getGyroDegrees(gyroSensor) <= 45)
	{
		motor[leftMotor] = 30;
		motor[rightMotor] = -30;
	}
	forward(800,milliseconds,40);
	while(getGyroDegrees(gyroSensor) >= 0)
	{
		motor[leftMotor] = -30;
		motor[rightMotor] = 30;
	}
	backward(200,milliseconds,40);
	forward(500,milliseconds,40);
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
	resetGyro(gyroSensor);
	while(getGyroDegrees(gyroSensor) <= 180)
	{
		motor[leftMotor] = 30;
		motor[rightMotor] = -30;
	}
	resetGyro(gyroSensor);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
	while(getGyroDegrees(gyroSensor) <=360)
	{
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		if(getColorName(colorSensor) != colorBlack)
		{
			motor[leftMotor] = 20;
			motor[rightMotor] = -20;
		}
		else if (getColorName(colorSensor) == colorBlack)
		{
			brx++;
			while(getColorName(colorSensor) == colorBlack)
			{
				motor[leftMotor] = 20;
				motor[rightMotor] = -20;
			}
		}
	}
	motor[motorB] =0;
	motor[motorC] =0;
	resetGyro(gyroSensor);
	while(getGyroDegrees(gyroSensor) <= 180)
	{
		motor[leftMotor] = 20;
		motor[rightMotor] = -20;
	}
	forward(300,milliseconds,30);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	passed = true;
	return brx - 1;
}

void createEmpty(){
//Menginisalisasi array route dan branch
//Kamus Lokal
	int i;

//Algoritma
	for (i = 0; i < 20; i++){
		branch[i] = -1; route[i] = -1; jml[i] = -1;
	}
	i = 0;
}

task main(){
//Kamus
	int r, j;
	bool stop = false; //boolean stop
	bool stop2 = false; //boolean stop2

//Algoritma
	//Inisialisasi
	createEmpty();
	//Maju jalan
	do {
		forward(300, milliseconds, 50);
		turnLeft (20, degrees, 30);
		getColorRGB(colorSensor, color[0], color[1], color[2]);
	} while (isBlue(color[0], color[1], color[2])==false);
	forward(500, milliseconds, 50);
	//Mencari jalan ke finish
	while (!stop){
		LineFollower();
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)){
			if (!passed){
				br = 0;
				br = countCabang();
				if (br == 3) {
					branch[top] = 3; top++;
					branch[top] = 2; top++;
					branch[top] = 1; top++;
				} else if (br == 2) {
					branch[top] = 2; top++;
					branch[top] = 1; top++;
				}
				jml[top2] = br;
				top2++;
			}
			turn_left();
			//Mengelola array
			top--;
			route[nr] = branch[top];
			nr++; branch[top] = -1;
		} else if (isRed(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorRed)){
			reverse();
		} else if (isBlue(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorBlue)){
			stop = true;
		}
	}
	stopAllMotors(); wait1Msec(10000);

	//Menampilkan Jalan
	for (j = 0; j < nr; j++){
		if (jml[j] == 3){
			if (route[j] == 1){
				displayTextLine((j + 1), "Kanan");
			} else if (route[j] == 2){
				displayTextLine((j + 1), "Lurus");
			} else if (route[j] == 3){
				displayTextLine((j + 1), "Kiri");
			}
		} else if (jml[j] == 2){
			if (route[j] == 1){
				displayTextLine((j + 1), "Kanan");
			} else if (route[j] == 2){
				displayTextLine((j + 1), "Kiri");
			}
		}
	}
	//Kembali ke start
	//Mengatur posisi
	forward(2000, milliseconds, 50);
	reverse_2();
	//Maju jalan
	do {
		forward(300, milliseconds, 50);
		turnLeft (20, degrees, 30);
		getColorRGB(colorSensor, color[0], color[1], color[2]);
	} while (isBlue(color[0], color[1], color[2])==false);
	forward(500, milliseconds, 50);
	//Berjalan kembali
	while (!stop2){
		LineFollower();
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)){
			nr--; r = route[nr]; top2--;
			if (jml[top2] == 3){
				if (r == 1){//belok kanan sebelumnya
					turn_left_2();
				} else if (r == 2){//lurus sebelumnya
					turn_left_3(0, 1, 1);
				} else if (r == 3){ //belok kiri sebelumnya
					turn_right_2();
				}
			} else if (jml[top2] == 2){
				if (r == 1){//belok kanan sebelumnya
					turn_left_2();
				} else if (r == 2){//lurus sebelumnya
					turn_right_2();
				}
			}
		} else if (isBlue(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorBlue)){
			stop2 = true;
		}
	}
}
