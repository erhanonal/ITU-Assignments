//Erhan Önal 150170713
class Vector{
	private:
		int size;
		int* values;
	public:
		Vector(int,int*);
		Vector(const Vector&);
		~Vector();
		Vector operator+(const Vector&) const;
		Vector operator*(int) const;
		int operator*(const Vector&) const;
		const Vector& operator=(const Vector&);
		friend std::ostream& operator<<(std::ostream&,const Vector&);
		int getSize();
		int* getValues();
};

