#pragma once
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#define BEOWULF 1

#define DRAGON 1
#define DRAGON_HEAD 1
#define DRAGON_FLAME 1
#define DRAGON_NECK 1
#define DRAGON_WINGS 1
#define DRAGON_LEGS 1

#define QUOTE 1

#define FANCY false

void setup_camera(){
	camera.w = 600;
	camera.h = 400;
	camera.c = 600;

	vec origin = { 5, 6, 0};
	// origin = { 0, 6, 0};

	float theta = M_PI * 0;
	theta = M_PI * 2.0 * camera.time / 5.0;
	// theta = M_PI * -0.3;
	camera.p = vec{ sin(theta)*24, 1, -cos(theta)*24 } + origin;

	camera.t.z = (camera.p-origin).norm() * -1.0;
	camera.t.init();

	camera.spp = 32;
	camera.sync = 1;
	camera.bounces = 5;

	if(FANCY){
		camera.spp = 64;
		camera.w *= 2;
		camera.h *= 2;
		camera.c *= 2;
	}
}

color sky(vec d){
	// return vec{.075, .06, .05};
	// if(FANCY) return vec{.1, .1, .1};
	// return vec{.5, .5, .5};
	return vec{.45, .35, .25};
	// return vec{1, 1, 1};
}

void line(vec a, vec b, material M, float W, vec _cam) {
	rects.push_back({
		.t = {
			.p = (a+b)*0.5,
			.y = _cam,
			.z = (a-b).norm(),
		},
		.m = M,
		.w = W, .l = (a-b).mag()/2,
	});
}

void line(vec a, vec b, material M, float W) {
	rects.push_back({
		.t = {
			.p = (a+b)*0.5,
			.y = camera.t.z,
			.z = (a-b).norm(),
		},
		.m = M,
		.w = W, .l = (a-b).mag()/2,
	});
}

void line(vec a, vec b, material M, float W, transform *t) {
	rects.push_back({
		.t = {
			.p = (a+b)*0.5,
			.y = camera.t.z,
			.z = (a-b).norm(),
			.t = t,
		},
		.m = M,
		.w = W, .l = (a-b).mag()/2,
	});
}

void setup_scene(){
	// ground
	
	rects.push_back({
		.t = {
			.p = { 0, 0, 0 },
			.y = { 0, 1, 0 },
			.z = { 0, 0, 1 },
		},
		.m = material::metal({.75, .75, .75}, 10),
		.w = 1000, .l = 60,
	});

	// beowulf
	
	if(BEOWULF){
		// head
		
		rects.push_back({
			.t = {
				.p = { 0.125, 5, 0.4 },
				.y = { 0, 0, 1 },
				.z = (vec{ 0.067, 1, 0 }).norm(),
			},
			.m = material::diffuse({0.1, 0.1, 0.1}),
			.w = .6, .l = .6,
		});

		rects.push_back({
			.t = {
				.p = { 0.125, 5, -0.4 },
				.y = { 0, 0, 1 },
				.z = (vec{ 0.067, 1, 0 }).norm(),
			},
			.m = material::diffuse({0.1, 0.1, 0.1}),
			.w = .6, .l = .6,
		});

		rects.push_back({
			.t = {
				.p = { 0.125, 5, 0 },
				.y = { 1, 0,  },
				.z = (vec{ 0.067, 1, 0 }).norm(),
			},
			.m = material::diffuse({0.1, 0.1, 0.1}),
			.w = .4, .l = .6,
		});

		// neck

		line(
			{ 0.25, 5.25, 0 },
			{ -0.25, 3.75, 0 },
			material::diffuse({0.87, 0.66, 0.45}),
			.2
		);

		// torso

		/*
		line(
			{ -0.25, 3.75, 0 },
			{ -1.3, 2, 0 },
			material::diffuse({0.87, 0.66, 0.45}),
			.15
		);
		*/

		vec Z = (vec{-1.3+.25, 2-3.75, 0}).norm(),
			X = (vec{-0.25, 0.05, 0.5}).norm(),
			Y = Z.cross(X);

		rects.push_back({
			.t = {
				.p = (vec{-.25-1.3, 3.75+2, 0})/2 + Y*0.15,
				.y = Y,
				.z = Z,
			},
			.m = material::diffuse(vec{0.87, 0.66, 0.45} * 0.7),
			.w = 0.5,
			.l = (vec{1.3-.25,1.75,0}).mag()/2,
		});

		rects.push_back({
			.t = {
				.p = (vec{-.25-1.3, 3.75+2, 0})/2 + Y*-0.2,
				.y = Y,
				.z = (Z+Y*0.2).norm(),
			},
			.m = material::diffuse(vec{0.87, 0.66, 0.45} * 0.85),
			.w = 0.5,
			.l = (vec{1.3-.25,1.75,0}).mag()/2,
		});

		rects.push_back({
			.t = {
				.p = vec{ -0.25, 3.75, 0 } - Y*0.15 + Z*0.2,
				.y = X,
				.z = Z,
			},
			.m = material::diffuse({0.87, 0.66, 0.45}),
			.w = 0.2, .l = 0.2,
		});

		// shield side

		{
			thread_local transform t1 = {
				.p = { -0.25, 0.05, 0.5 },
			};

			t1.init();

			// arm

			line(
				{ -0.25, 3.5, 0 },
				{ -1.6, 3.25, 0.25 },
				material::diffuse(vec{0.87, 0.66, 0.45}*0.9),
				.25, &t1
			);

			line(
				{ -1.4, 3.4, 0.25 },
				{ -2.3, 2.8, 1.25 },
				material::diffuse(vec{0.87, 0.66, 0.45}*0.85),
				.2, &t1
			);

			// shield

			rects.push_back({
				.t = {
					.p = { -2.3, 2.8, 1.3 },
					.y = (vec{ 0.2, 0.5, 1 }).norm(),
					.z = (vec{ 2, 1, 0 }).norm(),
					.t = &t1,
				},
				.m = material::metal({0.824, 0.684, 0.215}, 1000),
				.w = 1, .l = 1.6,
			});
		};

		// sword side

		{
			thread_local transform t1 = {
				.p = { 0.25, -0.125, -0.5 },
			};

			t1.init();

			// arm

			line(
				{ -0.25, 3.5, 0 },
				{ 1.25, 3, 0 },
				material::diffuse({0.87, 0.66, 0.45}),
				.25, &t1
			);

			line(
				{ 1, 3, 0 },
				{ 3, 3.25, 0 },
				material::diffuse({0.87*0.9, 0.66*0.9, 0.45*0.9}),
				.2, &t1
			);

			// sword

			{
				thread_local transform t2 = {
					.p = { 3, 3.25, 0.05 },
					.y = (vec{ -1, 3, 0 }).norm(),
					.z = (vec{ 0, 0, 1 }).norm(),
					.t = &t1,
				};

				t2.init();

				float sword_min = -1.5,
					  sword_max = 7.0,
					  guard_pos = 0.5,
					  guard_width = 0.6,
					  guard_depth = 0.08,
					  // blade_width = 0.09,
					  hilt_width = 0.08;

				unsigned char *img;
				int _w, _h;
				read_bmp("sword.bmp", &img, &_w, &_h);

				// blade
				masks.push_back({
					.t = {
						.p = { (guard_pos+sword_max)/2.0, 0, 0 },
						.y = { 0, 0, 1 },
						.z = { 0, 1, 0 },
						.t = &t2,
					},
					.m = material::light({6, 2, .75}),
					.image = img,
					.imgh = _h,
					.imgw = _w,
					.shiftx = 0,
					.shifty = 0,
					.sizex = _w,
					.sizey = _h,
					.w = (sword_max-guard_pos)/2.0,
					// .l = blade_width,
					.l = (sword_max-guard_pos)/2.0,
				});

				// hilt
				rects.push_back({
					.t = {
						.p = { (guard_pos+sword_min)/2.0, 0, 0 },
						.y = { 0, 0, 1 },
						.z = { 0, 1, 0 },
						.t = &t2,
					},
					.m = material::metal(vec{0.75, 0.625, 0.5}*0.5, 5),
					.w = (guard_pos-sword_min)/2.0, .l = hilt_width,
				});
				
				// guard
				rects.push_back({
					.t = {
						.p = { guard_pos, 0, 0 },
						.y = (vec{ 1, 0, 3 }).norm(),
						.z = (vec{ -3, 0, 1 }).norm(),
						.t = &t2,
					},
					.m = material::metal(vec{0.5, 0.5, 0.5}*0.5, 5),
					.w = guard_width, .l = guard_depth,
				});
			};
		};

		// hips

		/*
		line(
			{ -1.3, 2, -0.4 },
			{ -1.3, 2, 0.4 },
			material::metal({0.75, 0.25, 0.25}, 5),
			.15
		);
		*/

		// back leg

		line(
			{ -1.3, 2, 0.4 },
			{ -2.85, .85, 0.4 },
			material::diffuse(vec{0.87, 0.66, 0.45}*0.75),
			.275
		);

		line(
			{ -2.8, .875, 0.4 },
			{ -4.45, 0, 0.4 },
			material::diffuse(vec{0.87, 0.66, 0.45}*0.8),
			.225
		);

		// front leg

		line(
			{ -1.2, 2-0.1, -0.5 },
			{ .85, 1.65, -0.5 },
			material::diffuse(vec{0.87, 0.66, 0.45}*0.95),
			.275
		);

		line(
			{ .85, 1.65, -0.5 },
			{ .6, -0.1, -0.5 },
			material::diffuse(vec{0.87, 0.66, 0.45}*0.85),
			.225
		);
	};

	// dragon
	
	if(DRAGON){
		// neck

		float vert[5][2] = {
			{ 8.5, 6.8 },
			{ 9.3, 4.3 },
			{ 10.75, 2.25 },
			{ 13.5, 0.8 },
			{ 17.5, 0.2 },
		};

		float wid[4] = { 0.9, 0.95, 1.05, 1.1 };

		if(DRAGON_NECK) for(int i=0; i<4; ++i){
			vec c = {
				(vert[i][0]+vert[i+1][0])/2,
				(vert[i][1]+vert[i+1][1])/2,
				0,
			};

			vec D = {
				vert[i][0]-vert[i+1][0],
				vert[i][1]-vert[i+1][1],
				0,
			};

			vec d = D.norm();

			vec C = {
				c.x + d.y*wid[i],
				c.y - d.x*wid[i],
				c.z,
			};

			if(1){
				rects.push_back({
					.t = {
						.p = C,
						.y = { 0, 0, 1 },
						.z = d + vec{0, 0, i/10.0},
					},
					.m = material::metal({.25, .5, .25}, 10),
					.w = wid[i], .l = D.mag()/2,
				});

			}else for(int j=0; j<6; ++j){
					vec X = { d.y, -d.x, 0 };
					vec Y = X.cross(d);

					float theta = M_PI*2/6*j + (i+1)*0.618*M_PI*2;
					vec o = X*cos(theta) + Y*sin(theta);

					rects.push_back({
						.t = {
							.p = C + o*wid[i]*sqrt(3.0)/2,
							.y = (o+d*0.05).norm(),
							.z = (d-o*0.05).norm(),
						},
						.m = material::metal({.25, .5, .25}, 10),
						.w = wid[i]/2, .l = D.mag()/2,
					});
				}
		}

		// head

		if(DRAGON_HEAD){
			unsigned char *img;
			int _w, _h;
			read_bmp("head.bmp", &img, &_w, &_h);

			vec d = (vec{-1.5, 2, 0}).norm();

			thread_local transform t1 = {
				.p = vec{ 9.4, 7.5, 0 } + d*2.8,
				.y = { 0, 0, 1 },
				.z = d,
			};

			t1.init();

			float l = std::sqrt(2.8*2.8+1);

			masks.push_back({
				.t = {
					.p = { 0, -1, -2.8 },
					.y = (vec{ 0, -2.8, 1 }).norm(),
					.z = (vec{ 0, 1, 2.8 }).norm(),
					.t = &t1,
				},
				.m = material::metal({.2, .4, .2}, 10),
				.image = img,
				.imgh = _h,
				.imgw = _w,
				.shiftx = 0,
				.shifty = 0,
				.sizex = _w,
				.sizey = _h,
				.w = 1.4, .l = l,
			});

			masks.push_back({
				.t = {
					.p = { 0, 1, -2.8 },
					.y = (vec{ 0, -2.8, -1 }).norm(),
					.z = (vec{ 0, -1, 2.8 }).norm(),
					.t = &t1,
				},
				.m = material::metal({.15, .3, .15}, 10),
				.image = img,
				.imgh = _h,
				.imgw = _w,
				.shiftx = 0,
				.shifty = 0,
				.sizex = _w,
				.sizey = _h,
				.w = 1.4, .l = l,
			});

			// eye

			{
				unsigned char *img;
				int _w, _h;
				read_bmp("eye.bmp", &img, &_w, &_h);

				masks.push_back({
					.t = {
						.p = { 0, -1, -2.8 },
						.y = (vec{ 0, -2.8, 1 }).norm(),
						.z = (vec{ 0, 1, 2.8 }).norm(),
						.t = &t1,
					},
					.m = material::light({4, 2, 0}),
					.image = img,
					.imgh = _h,
					.imgw = _w,
					.shiftx = 0,
					.shifty = 0,
					.sizex = _w,
					.sizey = _h,
					.w = 1.4, .l = l,
				});
			};

			// extra horns

			{
				unsigned char *img;
				int _w, _h;
				read_bmp("horns.bmp", &img, &_w, &_h);

				masks.push_back({
					.t = {
						.p = { 0, -0.6, -2.8 },
						.y = (vec{ 0, -2.8, 1 }).norm(),
						.z = (vec{ 0, 1, 2.8 }).norm(),
						.t = &t1,
					},
					.m = material::metal({.15, .3, .15}, 10),
					.image = img,
					.imgh = _h,
					.imgw = _w,
					.shiftx = 0,
					.shifty = 0,
					.sizex = _w,
					.sizey = _h,
					.w = 1.4, .l = l,
				});
			};
		};

		// flame

		if(DRAGON_FLAME){
			thread_local transform t1 = {
				.p = { 11, 4, 0 },
				.y = { 0, 0, 1 },
				.z = (vec{5.5,13.5,0}-vec{11,4,0}).norm(),
			};

			t1.init();

			unsigned char *img;
			int _w, _h;
			read_bmp("flame.bmp", &img, &_w, &_h);

			float s = 1.0/8.0;

			masks.push_back({
				.t = {
					.p = { 0, 0, 7 },
					.t = &t1,
				},
				.m = material::light({4, 0.75, 0}),
				.image = img,
				.imgh = _h,
				.imgw = _w,
				.shiftx = 0,
				.shifty = 0,
				.sizex = _w,
				.sizey = _h,
				.w = 7*2*s, .l = 7,
			});
		};

		// legs

		if(DRAGON_LEGS){
			line(
				{ 14.5, 2, -0.2 },
				{ 13.5, 0.8, -1.4 },
				material::metal({.2, .4, .2}, 10),
				0.6, (vec{ 0, 1, -24 }).norm()
			);

			line(
				{ 13.8, 0.8, -1.4 },
				{ 11, 0, -2 },
				material::metal({.15, .3, .15}, 10),
				0.4, (vec{ 0, 1, -24 }).norm()
			);

			line(
				{ 14.5, 2, 0.5 },
				{ 13.5, 0.8, 1.4 },
				material::metal({.15, .3, .15}, 10),
				0.6, (vec{ 0, 1, 24 }).norm()
			);

			line(
				{ 13.8, 0.8, 1.4 },
				{ 11, 0, 2 },
				material::metal({.1, .2, .1}, 10),
				0.4, (vec{ 0, 1, 24 }).norm()
			);
		};

		// wings

		if(DRAGON_WINGS){
			vec z = (vec{2.5, 5, -4.8}).norm(),
				x = (vec{3.5, -1, 0}).norm(),
				y = x.cross(z);

			rects.push_back({
				.t = {
					.p = { 15.5+3.5/2, 4.75-0.5, -3.1 },
					.y = y,
					.z = z,
				},
				.m = material::metal({.2, .4, .2}, 10),
				.w = (vec{3.5, -1, 0}).mag()/2,
				.l = (vec{2.5, 5, 4.8}).mag()/2,
			});

			rects.push_back({
				.t = {
					.p = { 15.75+3.5/2, 4.5-0.5, 2.6 },
					.y = y*vec{1,1,-1},
					.z = z*vec{1,1,-1},
				},
				.m = material::metal({.25, .5, .25}, 10),
				.w = (vec{3.5, -1, 0}).mag()/2,
				.l = (vec{2.5, 5, 4.8}).mag()/2,
			});
		
			vec Y = (vec{0.7, 0, 1}).norm(),
				X = Y.cross({4,2,1}).norm();
			float W = 1.6;

			rects.push_back({
				.t = {
					.p = vec{ 16.9+3.27, 7.1+1.635, 5.1+0.815 } - X*W,
					.y = Y,
					.z = (vec{4, 2, 1}).norm(),
				},
				.m = material::metal({.25, .5, .25}, 10),
				.w = W,
				.l = (vec{3.27, 1.635, 0.815}).mag(),
			});
		};
	};

	// quote
	
	if(QUOTE){
		unsigned char *img;
		int _w, _h;
		read_bmp("quote.bmp", &img, &_w, &_h);

		float X = 0.005,
			  Y = -0.002,
			  W = 0.3;

		masks.push_back({
			.t = {
				.p = camera.p + camera.t.z*2
					-camera.t.x * camera.w/camera.c
					+camera.t.y * camera.h/camera.c
					+camera.t.x * X
					-camera.t.y * Y
					+camera.t.x * W
					-camera.t.y * W * (float(_h)) / (float(_w)),
				.y = camera.t.z,
				.z = camera.t.y,
			},
			.m = material::light({6, 2, .75}),
			.image = img,
			.imgh = _h,
			.imgw = _w,
			.shiftx = 0,
			.shifty = 0,
			.sizex = _w,
			.sizey = _h,
			.w = W, .l = W * (float(_h)) / (float(_w)),
		});
	};
}
