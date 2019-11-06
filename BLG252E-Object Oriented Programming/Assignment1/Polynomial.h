//Erhan Önal 150170713
class Polynomial{
	private:
		int degree;
		int* values;
	public:

		Polynomial(int, int*);
		Polynomial(const Polynomial&);
		~Polynomial();
		Polynomial operator+(const Polynomial& ) const;
		Polynomial operator*(const Polynomial& ) const;
		const Polynomial&  operator=(const Polynomial&);
		friend std::ostream& operator<<(std::ostream& ,const Polynomial&);
		int getDegree();
		int* getValues();	
};

