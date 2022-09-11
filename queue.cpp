#include <iostream>
#include <deque>
using namespace std;
#define T 1.0
#define QSIZE 10
#define INCQ 3

class Auto {
protected:
	int direction;
	double passing_coeff;
	bool id;
public:
	virtual int getDirection()=0;
	virtual double getCoeff()=0;
	virtual bool getId()=0;
	virtual void show()=0;
};

class Car: public Auto {
public:
	Car(int direction) {
		this->direction = direction;
		this->passing_coeff = 0.13 * T;
		this->id = 0;
	}
	int getDirection() override {
		return this->direction;
	}
	double getCoeff() override {
		return this->passing_coeff;
	}
	bool getId() override {
		return this->id;
	}
	void show() override {
		cout << "A car going ";
		if (this->direction < 0)
			cout << "from the left.";
		else if (this->direction > 0)
			cout << "from the right.";
		else
			cout << "straight.";
		cout << endl;
	}
};

class Truck: public Auto {
public:
	Truck(int direction) {
		this->direction = direction;
		this->passing_coeff = 2.3 * 0.13 * T;
		this->id = 1;
	}
	int getDirection() override {
		return this->direction;
	}
	double getCoeff() override {
		return this->passing_coeff;
	}
	bool getId() override {
		return this->id;
	}
	void show() override {
		cout << "A truck going ";
		if (this->direction < 0)
			cout << "from the left.";
		else if (this->direction > 0)
			cout << "from the right.";
		else
			cout << "straight.";
		cout << endl;
	}
};

class TrafficLight {
	double period;
	TrafficLight(int period = T) {
		this->period = period;
	}

public:
	double timeToPass(Auto *car) {
		double time = car->getCoeff();
		int dir { car->getDirection() };
		if (dir < 0)
			time *= 1.03;
		if (dir > 0)
			time *= 1.01;
		return time;
	}

	void passThrough(Auto *car) {
		double time = timeToPass(car);
		int dir { car->getDirection() };
		cout << "A ";
		if (!car->getId())
			cout << "car ";
		else
			cout << "truck ";
		cout << "has passed through the intersection ";
		if (dir < 0)
			cout << "from the left ";
		else if (dir > 0)
			cout << "from the right ";
		else
			cout << "straight ";
		cout << "in " << time << " time units";
		cout << endl;
	}
	friend class Crossroads;
};

class Crossroads {
	static TrafficLight *tl;
	deque<Auto*> q;
public:
	void enqueue(size_t n) {
		int dir { };
		bool id { };
		for (size_t i = 0; i < n; i++) {
			dir = -1 + rand() % 3;
			id = rand() % 2;
			if (id)
				this->q.push_back(new Truck(dir));
			else
				this->q.push_back(new Car(dir));
		}
	}

	Crossroads(size_t size = QSIZE, double period = T) {
		if (!this->tl)
			this->tl = new TrafficLight(period);
		this->enqueue(size);
	}

	TrafficLight* trafficLight() {
		if (!this->tl)
			this->tl = new TrafficLight();
		return this->tl;
	}

	void showQueue() {
		for (deque<Auto*>::iterator it = this->q.begin(); it != this->q.end();
				it++)
			(*it)->show();
	}

	void interval() {
		double totaltime { };
		while (!q.empty()) {
			if (totaltime + this->tl->timeToPass(q.front()) > this->tl->period)
				break;
			this->tl->passThrough(q.front());
			totaltime += this->tl->timeToPass(q.front());
			q.pop_front();
		}
		this->enqueue(INCQ);
	}

	void start() {
		int cmd { };
		do {
			if (this->q.empty())
				return;
			cout << "Current queue by the traffic light:" << endl;
			this->showQueue();
			cout
					<< "Enter 0 to exit or any other number to advance time by one traffic light period ("
					<< this->tl->period << " time units)" << endl;
			cin >> cmd;
			if (cmd) {
				this->interval();
				cout << "----" << endl << endl;
			}
		} while (cmd);
	}
};

TrafficLight *Crossroads::tl = nullptr;

int main() {

	Crossroads c;
	//c.interval();
	c.start();

	return 0;
}
