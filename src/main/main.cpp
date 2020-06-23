
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>
#include <numeric>

template <typename T>
struct RGB_basic
	{
	public:
		T R = T ( 0 );
		T G = T ( 0 );
		T B = T ( 0 );

		template<typename U>
		RGB_basic<T> operator* ( U mul ) const
			{
			RGB_basic<T> col ( R*mul, G*mul, B*mul );
			return col;
			}

		template<typename U>
		RGB_basic<T>& operator*= ( U mul )
			{
			R *= mul;
			G *= mul;
			B *= mul;

			return *this;
			}
	};

template <typename T>
struct  RGBA_basic : public RGB_basic<T>
	{
	public:
		T A = T ( 0 );

		RGBA_basic ( T r  = T ( 0 ), T g  = T ( 0 ), T b  = T ( 0 ), T a  = T ( 0 ) ) :
			RGB_basic<T>{r, g, b}, A{a}
			{}
	};

template <typename T>
struct Point2D_basic
	{
	public:
		T X = T ( 0 );
		T Y = T ( 0 );
	};

template < typename T>
struct Point3D_basic : public Point2D_basic<T>
	{
	public:
		T Z = T ( 0 );

		Point3D_basic ( T x = T ( 0 ), T y = T ( 0 ), T z = T ( 0 ) ) : Point2D_basic<T>{x, y}, Z{z}
			{}


		Point3D_basic<T> operator- ( const Point3D_basic<T>& sec ) const
			{
			return Point3D_basic<T> ( this->X-sec.X, this->Y-sec.Y, this->Z-sec.Z );
			}

		Point3D_basic<T> operator+ ( const Point3D_basic<T>& sec ) const
			{
			return Point3D_basic<T> ( this->X+sec.X, this->Y+sec.Y, this->Z+sec.Z );
			}

		Point3D_basic<T> operator* ( const Point3D_basic<T>& sec ) const
			{
			return Point3D_basic<T> ( this->X*sec.X, this->Y*sec.Y, this->Z*sec.Z );
			}

		Point3D_basic<T>& operator-= ( const Point3D_basic<T>& sec )
			{
			this->X -= sec.X;
			this->Y -= sec.Y;
			this->Z -= sec.Z;
			return *this;
			}

		Point3D_basic<T>& operator+= ( const Point3D_basic<T>& sec )
			{
			this->X += sec.X;
			this->Y += sec.Y;
			this->Z += sec.Z;
			return *this;
			}

		Point3D_basic<T>& operator*= ( const Point3D_basic<T>& sec )
			{
			this->X *= sec.X;
			this->Y *= sec.Y;
			this->Z *= sec.Z;
			return *this;
			}


		// by 1D constant
		Point3D_basic<T> operator- ( T val ) const
			{
			return Point3D_basic<T> ( this->X-val, this->Y-val, this->Z-val );
			}

		Point3D_basic<T> operator+ ( T val ) const
			{
			return Point3D_basic<T> ( this->X+val, this->Y+val, this->Z+val );
			}

		Point3D_basic<T> operator* ( T val ) const
			{
			return Point3D_basic<T> ( this->X*val, this->Y*val, this->Z*val );
			}

		Point3D_basic<T> operator/ ( T val ) const
			{
			return val ? *this* ( T ( 1 )/val ) : Point3D_basic<T>();
			}

		Point3D_basic<T>& operator-= ( T val )
			{
			this->X -= val;
			this->Y -= val;
			this->Z -= val;
			return *this;
			}

		Point3D_basic<T>& operator+= ( T val )
			{
			this->X += val;
			this->Y += val;
			this->Z += val;
			return *this;
			}

		Point3D_basic<T>& operator*= ( T val )
			{
			this->X *= val;
			this->Y *= val;
			this->Z *= val;
			return *this;
			}

		Point3D_basic<T>& operator/= ( T val )
			{
			return *this *= val ? ( T ( 1 ) / val ): Point3D_basic<T>();
			}

		T sum() const
			{
			return this->X + this->Y + Z;
			}

		T mul() const
			{
			return this->X*this->Y*Z;
			}

		static T dot ( const Point3D_basic<T>& first, const Point3D_basic<T>& second )
			{
			return ( first*second ).sum();
			}

		T norm() const
			{
			return std::sqrt ( dot ( *this, *this ) );
			}
	};

typedef float measurement_type;
typedef measurement_type type;
typedef RGB_basic<uint8_t> ColorType;
typedef Point2D_basic<measurement_type> Point2D;
typedef Point3D_basic<measurement_type> Point3D;
typedef Point2D_basic<measurement_type> Vec2;
typedef Point3D_basic<measurement_type> Vec3;
typedef Point3D_basic<measurement_type> Ray;


class Object
	{
	public:
		virtual bool checkCrossing ( const Point3D& x0, const Ray& ray, float& t, ColorType& cross_point_color ) = 0;

		virtual ~Object() {}
	};


class Ball : public Object
	{
	private:
		Point3D center_point;
		type radius;
		ColorType color;

	public:
		Ball ( const Point3D& center_, type radius_, ColorType color_ ) : center_point{center_}, radius{radius_}, color{color_}
			{}

		bool checkCrossing ( const Point3D& x0, const Ray& ray, float& t, ColorType& cross_point_color )
			{
			Vec3 oc = x0 - center_point;
			float b = Vec3::dot ( oc, ray );
			float c = Vec3::dot ( oc, oc ) - radius*radius;
			// delta
			float delta = b*b - c;
			// comlex result => no intersection
			if ( t < 0.0 )
				return false;

			t = -b - sqrt ( delta );
			// assign sphere color
			cross_point_color = color;

			return true;
			}

		~Ball()
			{
			}
	};


bool findColorForRay ( const Point3D& x0, const Ray& ray, ColorType& cross_point_color, std::vector<Object*>& objects )
	{
	type t = std::numeric_limits<type>::max();
	type aux;
	ColorType aux_color;
	bool found = false;

	// check all objects
	for ( Object* o : objects )
		{
		// if object is crossed and crossing point is not behind canvas and is closer than previous
		if ( o->checkCrossing ( x0, ray, aux, aux_color ) && ! ( aux < type ( 0.0 ) ) && aux < t )
			{
			t = aux;
			cross_point_color = aux_color;
			found = true;
			}
		}

	// true only if ray is crossing with some object
	return found;
	}

cv::Mat& render ( cv::Mat& canvas, const Point3D& camera_origin, const Vec3& distance, measurement_type width,
				  measurement_type height, std::vector<Object*>& objects )
	{
	measurement_type width_half = width / 2.0;
	measurement_type height_half = height / 2.0;

	for ( int row = 0; row < canvas.rows; ++row )
		{
		measurement_type dz = row*height/canvas.rows - height_half;

		for ( int col = 0; col < canvas.cols; ++col )
			{
			measurement_type dy = col*width/canvas.cols - width_half;

			Ray ray = distance+Vec3 ( dy, 0, dz );
			ColorType color;
			ray /= ray.norm();
			findColorForRay ( camera_origin, ray, color, objects );

			auto& pixel = canvas.at<cv::Vec3b> ( row, col );
			if ( color.R < 255 )
				std::cout << "";
			pixel[0] = color.R;
			pixel[1] = color.G;
			pixel[2] = color.B;
			}
		}

	return canvas;
	}


int main ( int argn, char* args[] )
	{
	cv::Mat img = cv::Mat ( 400, 600, CV_8UC3 );
	ColorType c0 {255, 100, 140}, c1{100, 50, 200}, c2{40, 255, 240} ;
	//RGBA_basic<uint8_t> colora {3, 5, 4, 4}, c2;
	Point3D p0{-1, 5, 0}, p1{0, 5, 0}, p2{1, 5, 0};
	type r0 = 0.5, r1 = 0.5, r2 = 0.5;

	std::vector<Object*> objects;
	Ball b0 = Ball ( p0, r0, c0 );
	Ball b1 = Ball ( p1, r1, c1 );
	Ball b2 = Ball ( p2, r2, c2 );

	objects.push_back ( &b0 );
	objects.push_back ( &b1 );
	objects.push_back ( &b2 );

	std::cout << "OK ????" << std::endl;
	Point3D camera_origin ( 0, 0, 0 );
	Vec3 distance ( 0, 1, 0 );
	measurement_type scale = 2;
	measurement_type width = 2.0*scale;
	measurement_type height = 3.0*scale;

	img = render ( img, camera_origin, distance, width, height, objects );

	std::cout << "OK ????" << std::endl;

	cv::Mat img2;
	cv::cvtColor ( img, img2, cv::COLOR_RGB2BGR );

	cv::imshow ( "Three balls", img2 );
	cv::waitKey ( 1000 );

	return 0;
	}