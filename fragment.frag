#version 330 core

layout (location = 0) out vec4 color;
varying vec2 pos;
uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

void main(){
	
	color = vec4(0.0,0.0,0.0,1.0);
	float distance = length(pos);

	//dot product untuk jam 
	float dotHour = dot(normalize(pos), vec2(cos(currentHourPointer), sin(currentHourPointer)));   // jarum

	if(distance <= 0.8){
		color = vec4(1.0, 1.0, 1.0, 1.0);
		if((dotHour) < sin(currentHourPointer)) color = vec4(1.0, 0.0, 0.0, 1.0);

		if(distance <= 0.7){  //size warna
			if((dotHour) < sin(currentHourPointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}

	
	//dot product untuk menit 
	float dotMenit = dot(normalize(pos), vec2(cos(currentMinutePointer), sin(currentMinutePointer)));   // jarum

	if(distance <= 0.6){
		if((dotMenit) < sin(currentMinutePointer)) color = vec4(0.0, 1.0, 0.0, 1.0);

		if(distance <= 0.5){  //size warna
			if((dotMenit) < sin(currentMinutePointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
	
	//dot product untuk detik 
	float dotDetik = dot(normalize(pos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));   // jarum

	if(distance <= 0.4){
		if((dotDetik) < sin(currentSecondPointer)) color = vec4(0.0, 0.0, 1.0, 1.0);
		// cout << currentSecondPointer <<endl;

		if(distance <= 0.3){  //size warna
			if((dotDetik) <  sin(currentSecondPointer)) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
}