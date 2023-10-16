#version 330 core

layout (location = 0) out vec4 color;
varying vec2 pos;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;
uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

void main(){


	// CLOCK DESIGN
	color = vec4(0.0,0.0,0.0,1.0);
	float distance = length(pos);

	//dot product untuk jam 
	float dotHour = dot(normalize(pos), vec2(0.8 * cos(currentHourPointer), 0.8 * sin(currentHourPointer)));   // jarum

	if(distance <= 0.8){
		color = vec4(1.0, 1.0, 1.0, 1.0);
		if((dotHour) < 0.8 * sin(currentHourPointer)) color = color1;

		if(distance <= 0.7){  //size warna
			if((dotHour) < 0.8 * sin(currentHourPointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}

	
	//dot product untuk menit 
	float dotMenit = dot(normalize(pos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));   // jarum

	if(distance <= 0.6){
		if((dotMenit) < 0.6 * sin(currentMinutePointer)) color = color2;

		if(distance <= 0.5){  //size warna
			if((dotMenit) < 0.6 * sin(currentMinutePointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
	
	//dot product untuk detik        0.0          -1, 0
	float dotDetik = dot(normalize(pos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));   // jarum

	if(distance <= 0.4){
		if((dotDetik) < sin(currentSecondPointer)) color = color3;
		// cout << currentSecondPointer <<endl;

		if(distance <= 0.3){  //size warna
			if((dotDetik) < sin(currentSecondPointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
}