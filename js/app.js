function setup(){
	createCanvas(400, 400);
}

function head(){
	const scale = 50;
	resizeCanvas(6*scale, 12*scale);
	background(255);

	// main head
	fill(0); noStroke();
	beginShape();
	let v = [
		[0, 1],
		[1, 0],
		[4.35, 1],
		[5, 0.6],
		[8, 2],
		[12, 2],
		[9, 3],
		[7.5, 4],
		[7, 5.5],
		[0.6, 6],
		[0, 5],
		[1.3, 5.3],
		[3, 5],
		[4, 4],
		[3, 2],
		[1, 1]
	];
	for(let V of v) vertex(V[1]*scale, V[0]*scale);
	endShape(CLOSE);

	// eye
	fill(255); noStroke();
	beginShape();
	v = [
		[4.75, 3.75/3.35],
		[5.5, 4.5/3.35],
		[5.5+0.25, 4.5/3.35-0.25*40/65],
		[5.11656, 0.8938]
	];
	for(let V of v) vertex(V[1]*scale, V[0]*scale);
	endShape(CLOSE);
}

function flame(){
	const scale = 100;
	resizeCanvas(2*scale, 8*scale);
	background(255);

	/*
	fill(200); noStroke();
	beginShape();
	vertex(0, 0);
	vertex(scale*2, 0);
	vertex(scale+scale/4, 6*scale);
	vertex(scale-scale/4, 6*scale);
	endShape(CLOSE);
	*/

	/*
	for(let i=0; i<2000; ++i){
		let a = Math.random(), b = a-Math.random()/8, c = Math.random();
		c = 1 - Math.acos(2*c-1)/Math.PI;
		stroke(0, 25); strokeWeight(scale/40);
		line(scale-(c-0.5)*(1-0.75*Math.min(a, b))*scale*2, Math.min(a, b)*scale*6,
		scale-(c-0.5)*(1-0.75*Math.max(a, b))*scale*2, Math.max(a, b)*scale*6);
	}
	*/

	for(let i=0; i<500; ++i){
		let x = Math.random(), y = Math.random(), r = (Math.random()+1)/2/8, theta = Math.random()*Math.PI*2;
		x = 1 - Math.acos(2*x-1)/Math.PI;
		function t(X, Y){
			// return [scale*2*X, scale*2*Y+scale*3];
			return [scale-(X-0.5)*(1-0.75*Y)*scale*2, scale*6*Y];
		}
		fill(0, 50); noStroke();
		beginShape();
		vertex(...t(x + r*Math.cos(theta), y + r*Math.sin(theta)));
		vertex(...t(x + r*Math.cos(theta+Math.PI*2/3), y + r*Math.sin(theta+Math.PI*2/3)));
		vertex(...t(x + r*Math.cos(theta+Math.PI*4/3), y + r*Math.sin(theta+Math.PI*4/3)));
		endShape(CLOSE);
	}
}

function eye(){
	const scale = 50;
	resizeCanvas(6*scale, 12*scale);
	background(255);

	fill(0); noStroke();
	beginShape();
	v = [
		[4.75, 3.75/3.35],
		[5.5, 4.5/3.35],
		[5.5+0.25, 4.5/3.35-0.25*40/65],
		[5.11656, 0.8938]
	];
	for(let V of v) vertex(V[1]*scale, V[0]*scale);
	endShape(CLOSE);
}

function horns(){
	const scale = 50;
	resizeCanvas(6*scale, 12*scale);
	background(255);

	// main head
	fill(0); noStroke();
	beginShape();
	let v = [
		[6, 4],
		[8, 3],
		[10, 4],
		[8, 4],
		[8.5, 5]
	];
	for(let V of v) vertex(V[1]*scale, V[0]*scale);
	endShape(CLOSE);
}

function sword(){
	const scale = 600;
	const aspect = 0.19/6.5;
	resizeCanvas(scale, scale);
	background(255);
	
	/*
	// base
	fill(200); noStroke();
	beginShape();
	vertex(0, scale/2-1.5*scale*aspect/2);
	vertex(scale-scale*aspect/2, scale/2-scale*aspect/2);
	vertex(scale, scale/2);
	vertex(scale-scale*aspect/2, scale/2+scale*aspect/2);
	vertex(0, scale/2+1.5*scale*aspect/2);
	endShape(CLOSE);
	*/

	/*
	// segment 1
	fill(0); noStroke();
	beginShape();
	vertex(0, scale/2-1.5*scale*aspect/2);
	vertex(scale*0.220289, scale/2+scale*-0.020289);
	vertex(scale*0.179407, scale/2+scale*0.020593);
	vertex(0, scale/2+1.5*scale*aspect/2);
	endShape(CLOSE);

	// segment 2
	push();
	translate(0, scale/100);
	// translate(-scale/50, 0);
	translate(scale*0.3, scale/2);
	rotate(-0.015);
	// rotate(-0.3);
	translate(-scale*0.3, -scale/2);
	fill(0); noStroke();
	beginShape();
	vertex(scale*0.220289, scale/2+scale*-0.020289);
	vertex(scale*0.380902, scale/2+scale*-0.019098);
	vertex(scale*0.418817, scale/2+scale*0.018817);
	vertex(scale*0.179407, scale/2+scale*0.020593);
	endShape(CLOSE);
	pop();

	// segment 3
	push();
	// translate(-scale/30, -scale/40);
	translate(scale*0.5, scale/2);
	rotate(0.02);
	// rotate(0.2);
	translate(-scale*0.5, -scale/2);
	fill(0); noStroke();
	beginShape();
	vertex(scale*0.380902, scale/2+scale*-0.019098);
	vertex(scale*0.617345, scale/2+scale*-0.017345);
	vertex(scale*0.582396, scale/2+scale*0.017604);
	vertex(scale*0.418817, scale/2+scale*0.018817);
	endShape(CLOSE);
	pop();

	// segment 4
	push();
	translate(0, scale/100);
	// translate(-scale/12, scale/50);
	translate(scale*0.7, scale/2);
	rotate(-0.05);
	// rotate(-0.1);
	translate(-scale*0.7, -scale/2);
	fill(0); noStroke();
	beginShape();
	vertex(scale*0.617345, scale/2+scale*-0.017345);
	vertex(scale*0.78389, scale/2+scale*-0.01611);
	vertex(scale*0.815873, scale/2+scale*0.015873);
	vertex(scale*0.582396, scale/2+scale*0.017604);
	endShape(CLOSE);
	pop();

	// segment 5
	push();
	translate(0, -scale/300);
	// translate(-scale/10, -scale/500);
	translate(scale*0.9, scale/2);
	rotate(0.01);
	// rotate(0.05);
	translate(-scale*0.9, -scale/2);
	fill(0); noStroke();
	beginShape();
	vertex(scale*0.78389, scale/2+scale*-0.01611);
	vertex(scale-scale*aspect/2, scale/2-scale*aspect/2);
	vertex(scale, scale/2);
	vertex(scale-scale*aspect/2, scale/2+scale*aspect/2);
	vertex(scale*0.815873, scale/2+scale*0.015873);
	endShape(CLOSE);
	pop();
	*/

	let A = [
		[0.179407, 0.020593],
		[0.369185, 0.019185],
		[0.582396, 0.017604],
		[0.666977, 0.016977],
		[0.834264, 0.015736],
	], B = [
		[0.220289, 0.020289],
		[0.330529, 0.019472],
		[0.617345, 0.017345],
		[0.632770, 0.017230],
		[0.865504, 0.015504],
	], C = [
		0,
		-0.2,
		0.1,
		-0.4,
		-0.1,
		-1.2,
	], D = [
		[0, 0],
		[-0.005, 0.05],
		[-0.055, -0.02],
		[-0.07, 0.03],
		[-0.07, -0.00],
		[-0.075, 0.02],
	];

	fill(0); noStroke();

	push();
	translate(D[0][0]*scale, D[0][1]*scale);
	translate(scale*0.1, scale/2);
	rotate(C[0]);
	translate(-scale*0.1, -scale/2);
	beginShape();
	vertex(0, scale/2-1.5*scale*aspect/2);
	vertex(scale*B[0][0], scale/2-scale*B[0][1]);
	vertex(scale*A[0][0], scale/2+scale*A[0][1]);
	vertex(0, scale/2+1.5*scale*aspect/2);
	endShape(CLOSE);
	pop();

	for(let i=1; i<5; ++i){
		push();
		translate(D[i][0]*scale, D[i][1]*scale);
		translate(scale*(0.1+i*0.2), scale/2);
		rotate(C[i]);
		translate(-scale*(0.1+i*0.2), -scale/2);
		beginShape();
		vertex(scale*B[i-1][0], scale/2-scale*B[i-1][1]);
		vertex(scale*B[i][0], scale/2-scale*B[i][1]);
		vertex(scale*A[i][0], scale/2+scale*A[i][1]);
		vertex(scale*A[i-1][0], scale/2+scale*A[i-1][1]);
		endShape(CLOSE);
		pop();
	}

	push();
	translate(D[5][0]*scale, D[5][1]*scale);
	translate(scale*0.9, scale/2);
	rotate(C[5]);
	translate(-scale*0.9, -scale/2);
	beginShape();
	vertex(scale*B[4][0], scale/2-scale*B[4][1]);
	vertex(scale-scale*aspect/2, scale/2-scale*aspect/2);
	vertex(scale, scale/2);
	vertex(scale-scale*aspect/2, scale/2+scale*aspect/2);
	vertex(scale*A[4][0], scale/2+scale*A[4][1]);
	endShape(CLOSE);
	pop();
}

function draw(){
	// head();
	
	// flame();
	
	// eye();
	
	// horns();
	
	sword();
	
	noLoop();
}
