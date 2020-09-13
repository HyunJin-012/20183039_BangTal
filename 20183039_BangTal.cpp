#include <bangtal.h>
using namespace bangtal;

int main()
{
	//1. 장면을 생성한다
	auto scene0 = Scene::create("Intro", "Images/처음.png");
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	scene0->setLight(0.7f);
	scene1->setLight(0.7f);
	scene2->setLight(0.7f);

	auto message = Object::create("Images/명령.png", scene0, 100, 270);
	message->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});


	//열쇠를 생성한다
	auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);		  //열쇠 크기 조정(소수니까 f지정)

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();			 //클릭해서 열쇠를 집음
		return true;
		});

	//화분을 생성한다(+좌우이동, 화분의 이동상태 저장) 열쇠->화분 순으로 작성해야 열쇠가 가려짐.
	auto flowerpot_moved = false;   //화분이 움직이지 않은 상태임
	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	auto clock = Object::create("Images/시계.png", scene1, 350, 550);
	clock->setScale(0.08f);
	auto schrank_moved = false;
	auto schrank = Object::create("Images/옷장.png", scene1, -60, 210);
	schrank->setScale(0.5f);
	schrank->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (schrank_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				schrank->locate(scene1, -75, 210);
				schrank_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				schrank->locate(scene1, -20, 210);
				schrank_moved = true;
			}
		}
		return true;
		});

	auto table_moved = false;
	auto table = Object::create("Images/식탁.png", scene1, 890, 90);
	table->setScale(0.35f);
	table->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (schrank_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				table->locate(scene1, 870, 90);
				table_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				table->locate(scene1, 920, 90);
				table_moved = true;
			}
		}
		return true;
		});



	//3. 문을 생성한다
	auto open1 = false;			  //문의 열림상태를 위한 변수
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);


	//4. 문을 클릭하면 이동한다   //lamda Function(오브젝트, x좌표,y좌표,마우스이벤트)
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//5. 문이 열린 상태이면 scene2로 이동한다.
		//	 문이 닫힌 상태이면 문을 열어준다
		if (open1 == true) {
			scene2->enter();    //scene2로 이동
		}
		else if (key->isHanded()) {
			door1->setImage("Images/문-오른쪽-열림.png");  //door은 포인터이므로 ->로 호출
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!!");
		}

		return true;
		});

	//scene2의 문을 생성한다
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();          //scene2 왼쪽 문을 클릭하면 scene1으로 이동
		return true;
		});

	auto open3 = false, locked3 = true;    //door3가 닫혀있는,잠겨진 상태임
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270,false);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction acton)->bool {
		door3->setImage("Images/문-오른쪽-열림.png");
		open3 = true;
		endGame();
		                        
		return true;
		});

	//스위치 생성
	auto lighted = true;   //스위치 상태 변수
	auto button = Object::create("Images/스위치.png", scene2, 850, 440);
	button->setScale(0.05f);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {     //켜진상태
			scene2->setLight(0.3f);
			door3->show();
			lighted = false;
		}
		else {              //꺼진상태
			scene2->setLight(1.0f);
			door3->hide();
			lighted = true;
		}
		return true;
		});

	auto sofa = Object::create("Images/소파.png", scene2, 370, 80);
	sofa->setScale(0.55f);

	//2 게임을 시작한다
	startGame(scene0);

	return 0;
}


