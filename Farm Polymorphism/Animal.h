class Animal {
public:
	virtual void MakeSound() = 0;
	
protected:
	int currentSize;
	int maxSize;
};

class Dog : public Animal
{
	public: 
		void MakeSound();

	private:
};

class Cat : public Animal
{
	public:
		void MakeSound();

	private:
};

class Pig : public Animal
{
	public: 
		void MakeSound();

	private:
};

class Cow : public Animal
{
	public:
		void MakeSound();

	private:
};

class Ranch {

public:
	Ranch();
	~Ranch();
	Ranch(const Ranch&);
	void operator=(const Ranch&);
	void Grow();
	void AddDog();
	void AddCat();
	void AddPig();
	void AddCow();
	void Menu();
	void Print();
private:
	Animal** ranch;
	int currentSize;
	int maxSize; 
};
