#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <argparse.hpp>
#include <tabulate.hpp>
#include <sstream>
#include <csv2.hpp>

using namespace tabulate;
using namespace csv2;

#define PI 3.14159265358979323846
#define K 8.988E+9
#define ELECTRON_CHARGE -1.60221766E-19

class P {
	public:
		long double x,y,q,fx,fy,magf,netangle;
		P(long double a, long double b, long double c) {
			x = a;
			y = b;
			q = c;
		}
};
// This function takes the doubles of the point charge
// and makes them into strings, keeping scientific notation
// for numbers that are very large/small
std::string conv(double cat) {
	std::ostringstream so;
	so << cat;
	std::string sro = so.str();
	return sro;

}

// writes data to csv file
void write(std::string outfile, std::vector<P> points){
	std::ofstream stream(outfile);
	Writer<delimiter<','>> writer(stream);
	std::vector<std::string> holder;
	holder.push_back("x");
	holder.push_back("y");
	holder.push_back("q");
	holder.push_back("F_net");
	holder.push_back("F_x");
	holder.push_back("F_y");
	holder.push_back("Angle");
	writer.write_row(holder);
	holder.clear();
	for(auto &p : points) {
		holder.push_back(conv(p.x));	
		holder.push_back(conv(p.y));
		holder.push_back(conv(p.q));
		holder.push_back(conv(p.magf));
		holder.push_back(conv(p.fx));
		holder.push_back(conv(p.fy));
		holder.push_back(conv(p.netangle));
		writer.write_row(holder);
		holder.clear();

	}
	stream.close();
	std::cout << "Stream closed: " << outfile << " written.";
}




// retrieves point charges from file and stores in a vector of P objects.
std::vector<P> getPoints(std::string filename){
	std::vector<P> points;
	std::string st_x, st_y, st_q;
	int index_x;
	int index_y;
	int index_q;
	std::string remainder;
	int start =0, end;
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> myvec;
	while (std::getline(infile, line)) {
		if (line[0] == '#') {
			continue;
		}
		index_x = line.find(',');
		end = index_x;
		st_x = line.substr(0,start+index_x);
		line = line.substr(end+1, std::string::npos);
		index_x = line.find(',');
		st_y = line.substr(start,start+index_x);
		line = line.substr(start+index_x+1, std::string::npos);
		st_q = line;
		points.push_back(P(stold(st_x),stold(st_y),stold(st_q)));
	}
	return points;

}

int main(int argc, char *argv[]){
	argparse::ArgumentParser program("zap");
	program.add_argument("infile").help("file to read");
	try {
	program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
	  std::cerr << err.what() << "\n";
	  std::cerr << program;
	  std::exit(1);
	}
	std::string infile = program.get<std::string>("infile");
	std::vector<P> p = getPoints(infile);
	int elems = p.size();
	long double x_dist, y_dist, dist, totalforce, angle, fx, fy;
	for (int i = 0; i < elems; ++i) {
		for (int j = 0; j < elems; ++j) {
			if (i!=j) {
				x_dist = fabsl(p[i].x - p[j].x);
				y_dist = fabsl(p[i].y - p[j].y);
				dist = sqrt((x_dist*x_dist)+(y_dist*y_dist));
				totalforce = (K*p[i].q*p[j].q)/(dist*dist);
				angle = atan2(y_dist,x_dist);
				fx = fabsl(totalforce*cosl(angle));
				fy = fabsl(totalforce*sinl(angle));
				if ((p[j].x < p[i].x) && (p[i].q * p[j].q <0)) {fx=-fx;}
				if ((p[j].x > p[i].x) && (p[i].q * p[j].q >0)) {fx=-fx;}
				if ((p[j].y < p[i].y) && (p[i].q * p[j].q <0)) {fy=-fy;}
				if ((p[j].y > p[i].y) && (p[i].q * p[j].q >0)) {fy=-fy;}
				p[i].fx = p[i].fx + fx;
				p[i].fy = p[i].fy + fy;
				
			}
		}
	}
	Table u;
	u.add_row({"x","y","q","Fnet", "Fx", "Fy", "angle"});
	for (int k = 0; k < elems; ++k) {
		p[k].magf = sqrt((p[k].fx*p[k].fx)+(p[k].fy*p[k].fy));
		p[k].netangle = atan2(p[k].fy, p[k].fx);
		u.add_row({conv(p[k].x),
				conv(p[k].y),
				conv(p[k].q),
				conv(p[k].magf),
				conv(p[k].fx),
				conv(p[k].fy),
				conv(p[k].netangle)});
	}
	u.format().font_style({FontStyle::bold})
		  .border_top(" ")
		  .border_bottom(" ")
		  .border_left(" ")
		  .border_right(" ")
		  .corner(" ");
	u[0].format()
	  .padding_top(1)
	  .padding_bottom(1)
	  .font_align(FontAlign::center)
	  .font_style({FontStyle::underline})
	  .font_background_color({Color::red});
	std::cout << u << "\n";
	write("dog.csv",p);
	return 0;
}









