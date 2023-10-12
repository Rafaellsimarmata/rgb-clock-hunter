#version 330 core

layout (location = 0) out vec4 color;
varying vec2 pos;

void main(){
	
	color = vec4(0.0,0.0,0.0,1.0);
	float distance = length(pos);

	//dot product untuk jam 
	float dot = dot(pos, vec2(-0.725, 0.725));   // jarum
	float cosAngle = dot / (length(pos) * length(vec2(1.0, 0.0)));

	if(distance <= 0.8){
		color = vec4(1.0, 1.0, 1.0, 1.0);
		if((cosAngle) > 0.72) color = vec4(1.0, 0.0, 0.0, 1.0);

		if(distance <= 0.7){  //size warna
			if((cosAngle) > 0.72) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}

	
	//dot product untuk menit 
	float dotMenit = dot(normalize(pos), vec2(0.0, 1.0));   // jarum

	if(distance <= 0.6){
		if(abs(dotMenit) > 0.0) color = vec4(0.0, 1.0, 0.0, 1.0);

		if(distance <= 0.5){  //size warna
			if(abs(dotMenit) > 0.0) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
	
	//dot product untuk detik 
	float dotDetik = dot(normalize(pos), vec2(1.0, 0.0));   // jarum

	if(distance <= 0.4){
		if((dotDetik) > 0.0) color = vec4(0.0, 0.0, 1.0, 1.0);

		if(distance <= 0.3){  //size warna
			if((dotDetik) > 0.0) color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
}