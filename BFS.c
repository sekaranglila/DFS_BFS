#pragma config(StandardModel, "EV3_REMBOT")

/*	NIM/Nama	:		13514004/Catherine Pricilla
									13514063/Steffi Indrayani
									13514071/Sekar Anglila Hapsari
		Nama File :		BFS.c
		Topik			:		DFS dan BFS
*/

//KAMUS
	struct ListofPath{
		int path[20];
	}
	int nr = 0; //Counter jalan yang sudah diambil
	int br = 0;
	int pos = 0;
	int top = 0;
	int level = 0;
	long color[3];
	ListofPath branch[20]; //Cabang
	int route[20];
	int ROUTEPATH[20];
	int now = 0;
	int idxR = 0;



//PROSEDUR DAN FUNGSI
bool isBlue (long red, long green, long blue) {
	if ((blue >= 0) && ((blue-red) > 50) && ((blue-green) > 50)) return true;
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


void reverse() {
//Robot berputar balik
//Algoritma
	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(1000);					    // Robot runs previous code for 750 milliseconds before moving on
	//Menghapus array
}

void reverse_2() {
//Robot berputar balik
//Algoritma
	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(1000);
}

void turn_right(){
//Membelokkan robot ke kanan
//Kamus Lokal
	bool black = false;

//Algoritma
	//Atur Posisi terlebih dahulu
	turnRight(30, degrees, 50);
	backward(400, milliseconds, 50);
	stopAllMotors(); wait1Msec(500);
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 30);
	wait1Msec(1500);
	forward(500, milliseconds, 50);
	stopAllMotors(); wait1Msec(500);

	//Belok kiri
	while(!black)
	{
		setMotorSpeed(leftMotor, 100);
		setMotorSpeed(rightMotor, 30);
		if(getColorReflected(colorSensor) < 65)
		{
			black = true;
		}
	}
}

void turn_right_2(){
//Membelokkan robot ke jalur kanan
	//Algoritma
	bool black = false;
	//Atur Posisi terlebih dahulu
	backward(400, milliseconds, 50);
	stopAllMotors(); wait1Msec(5000);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 0);
	wait1Msec(1500);
	forward(500, milliseconds, 50);
	stopAllMotors(); wait1Msec(5000);

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
	stopAllMotors(); wait1Msec(500);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 0);
	wait1Msec(1500);
	forward(500, milliseconds, 50);
	stopAllMotors(); wait1Msec(500);

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
	//passed = false;
}

void turn_left_2(){
//Membelokkan robot ke jalur kanan
//Kamus Lokal
	bool black = false;

//Algoritma
	//Atur Posisi terlebih dahulu
	backward(500, milliseconds, 50);
	stopAllMotors(); wait1Msec(500);
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 30);
	wait1Msec(1500);
	stopAllMotors(); wait1Msec(500);

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
	while(!stop){
		setMotorSpeed(leftMotor, -20);
		setMotorSpeed(rightMotor, 20);
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

void turn_right_3(int cabangAwal, int cabangAkhir, int ncabang) {
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
	while(!stop){
		setMotorSpeed(leftMotor, 20);
		setMotorSpeed(rightMotor, -20);
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
	//passed = true;
	return brx - 1;
}


void createEmpty(){
//Menginisalisasi array route dan branch
//Kamus Lokal
	int i;
	int j;
//Algoritma
	i = 0;
	for (i = 0; i < 20; i++) {
		for (j =0; j < 20; j++) {
			branch[i].path[j] = -1;
			ROUTEPATH[i] = -1;
		}
	}
}

void createEmptyRoute() {
	int i;
	for (i = 0; i < 20; i++){
		route[i] = -1;
	}
}

void AddToBranch() {
	int idx;
	for (idx = 0; idx <= idxR; idx++) {
		branch[top].path[idx] = route[idx];
	}
}

void gotonode() {
	now = 0; idxR = 0;
	while (branch[pos].path[now] != -1) {
		if (branch[pos].path[now] == 1) {
			turn_left();
			LineFollower();
			route[idxR] = 1;
		}
		else if (branch[pos].path[now] == 2) {
			turn_left_3(0,2,2);
			LineFollower();
			route[idxR] = 2;
		}
		else if (branch[pos].path[now] == 3) {
			turn_right();
			LineFollower();
			route[idxR] = 3;
		}
		idxR++;
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			now++;
		}
		else if (isRed(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			stopAllMotors();
			now++;
			route[idxR] = -1;
		}
		else if (isRed(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			stopAllMotors();
			now++;
			route[idxR] = -1;
		}
	}
}

void backToRoot() {
	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on
	forward();
	LineFollower();
	now--;
	while (now > 0) {
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			if (branch[pos].path[now] == 1) {
				turn_left_2();
				LineFollower();
			}
			else if (branch[pos].path[now] == 2) {
				turn_right_3(1,2,2);
				LineFollower();
			}
			else if (branch[pos].path[now] == 3) {
				turn_left();
				LineFollower();
			}
			now--;
		}
	}
	SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
	getColorRGB(colorSensor, color[0], color[1], color[2]);
	if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
		if (branch[pos].path[now] == 1) {
			turn_left_2();
			forward();
		}
		else if (branch[pos].path[now] == 2) {
			turn_right_3(1,2,2);
			stopAllMotors(); wait1Msec(500);
			while(getGyroDegrees(gyroSensor) <= 180)
			{
				motor[leftMotor] = 20;
				motor[rightMotor] = -20;
			}
			forward();
			motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
			motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
			wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on
		}
		else if (branch[pos].path[now] == 3) {
			setMotorSpeed(leftMotor, 30);
			setMotorSpeed(rightMotor, 0);
			wait1Msec(1500);
			forward(500, milliseconds, 50);
			stopAllMotors(); wait1Msec(500);
			bool black = false;
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
			stopAllMotors(); wait1Msec(500);
			forward();
			motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
			motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
			wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on

		}
		LineFollower();
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			stopAllMotors();
		}
	}
}


task main(){
	bool stop = false;
	createEmpty();
	do {
		forward(300, milliseconds, 50);
		turnLeft (15, degrees, 30);
		getColorRGB(colorSensor, color[0], color[1], color[2]);
	} while (isBlue(color[0], color[1], color[2])==false);
	forward(500, milliseconds, 50);
	LineFollower();
	SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
	getColorRGB(colorSensor, color[0], color[1], color[2]);
	//Ketemu hijau pertama;
	if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
		br = countCabang();
		int idx; top = 1;
		for (idx  = 0; idx < br; idx++) {
			branch[top].path[0] = idx+1; top++;
		}

	}

	while (!stop) {
		//Maju
		pos++;
		createEmptyRoute();
		gotonode();
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			br = countCabang();
			int idx;
			route[idxR] = 1;
			for (idx = 0; idx < br; idx++) {
				AddToBranch(); top++;
				route[idxR]++;
			}
		}
		else if (isBlue(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorBlue)) {
			stopAllMotors();
			stop = true;
		}
		backToRoot();
	}

	int i = 0;
	//Menampilkan route
	while (branch[pos].path[i] != -1) {
		ROUTEPATH[i] = branch[pos].path[i];
		if (ROUTEPATH[i] == 1) {
			displayTextLine(i, "Kanan");
		}
		else {
			displayTextLine(i, "Kiri");
		}
	}

	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on
	forward();
	//Berjalan kembali
	motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
	motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
	wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on
	forward();
	LineFollower();
	now--;
	while (now > 0) {
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			if (ROUTEPATH[now] == 1) {
				turn_left_2();
				LineFollower();
			}
			else if (ROUTEPATH[now] == 2) {
				turn_right_3(1,2,2);
				LineFollower();
			}
			else if (ROUTEPATH[now] == 3) {
				turn_left();
				LineFollower();
			}
			now--;
		}
	}
	SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
	getColorRGB(colorSensor, color[0], color[1], color[2]);
	if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
		if (ROUTEPATH[now] == 1) {
			turn_left_2();
			forward();
		}
		else if (ROUTEPATH[now] == 2) {
			turn_right_3(1,2,2);
			stopAllMotors(); wait1Msec(500);
			while(getGyroDegrees(gyroSensor) <= 180)
			{
				motor[leftMotor] = 20;
				motor[rightMotor] = -20;
			}
			forward();
			motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
			motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
			wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on
		}
		else if (ROUTEPATH[now] == 3) {
			setMotorSpeed(leftMotor, 30);
			setMotorSpeed(rightMotor, 0);
			wait1Msec(1500);
			forward(500, milliseconds, 50);
			stopAllMotors(); wait1Msec(500);
			bool black = false;
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
			stopAllMotors(); wait1Msec(500);
			forward();
			motor[rightMotor] = 0;		    // Motor on motorB is stopped at 0 power
			motor[leftMotor]  = 100;			// Motor on motorC is run at full (100) power forward
			wait1Msec(960);					    // Robot runs previous code for 750 milliseconds before moving on

		}
		LineFollower();
		SensorMode[colorSensor] = modeEV3Color_RGB_Raw;
		getColorRGB(colorSensor, color[0], color[1], color[2]);
		if (isGreen(color[0], color[1], color[2]) || (getColorName(colorSensor) == colorGreen)) {
			stopAllMotors();
		}
	}


}
