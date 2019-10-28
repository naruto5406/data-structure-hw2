#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;
class Term{
	friend class Polynomial;
	
	public:
		unsigned long coef;
		int exp;
}; 

class Polynomial{
	friend ostream & operator << (ostream &o, const Polynomial &poly);
	
	public:
		Polynomial();
		Polynomial(const Polynomial &poly);
		~Polynomial();
		
		Polynomial operator+(const Polynomial &poly);
		Polynomial operator*(const Polynomial &poly);
		Polynomial operator%(const Polynomial &poly);
		Polynomial operator/(const Polynomial &poly);
		
		float Eval(float x);
		
		void NewTerm(unsigned long coef, int exp);
		
	private:
		Term *termArray;
		int capacity;
		int terms;
		
		void insertTerm(const Term & term);
		
};

Polynomial::Polynomial(){
	this->terms = 0;
	this->capacity = 10;
	termArray = new Term[this->capacity];
}

Polynomial::Polynomial(const Polynomial &p){
	this->terms = 0;
	this->capacity = p.capacity;
	termArray = new Term[this->capacity];
	for(int i = 0; i < capacity; i++){
		NewTerm(p.termArray[i].coef, p.termArray[i].exp);
	}	
}

Polynomial::~Polynomial(){
	delete[] termArray;
}

Polynomial Polynomial::operator+(const Polynomial & b)  
{  
    Polynomial c;  
    int aPos = 0, bPos = 0;  
    while(aPos < terms && bPos < b.terms){  
        if(termArray[aPos].exp == b.termArray[bPos].exp){  
            unsigned long coef = termArray[aPos].coef + b.termArray[bPos].coef;  
            if(coef){
            	c.NewTerm(coef,termArray[aPos].exp);  
            	aPos++;
				bPos++;  
			}
            
        }
		else if(termArray[bPos].exp < b.termArray[bPos].exp){  
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);  
            bPos++;  
        }else{  
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);  
            aPos++;  
        }  
    }  
    while (aPos < terms){  
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);  
        aPos++;  
    }  
    while (bPos < b.terms){  
        c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);  
        bPos++;  
    }  
    return c;  
}  
Polynomial Polynomial::operator-(const Polynomial & b)  
{  
    Polynomial c;  
    new Polynomial b_temp = b;
    for(int i = 0; i < terms; i++){
    	b_temp.termArray[i].coef = (-1) * b.termArray[i].coef;	    	
	}
	
	c = *this + b_temp;
	return c;
}  

Polynomial Polynomial::operator*(const Polynomial & b)  
{  
    Polynomial c;  
    for(int i = 0; i < terms; i++){  
        for(int j=0; j<b.terms; j++){  
            unsigned long coef = termArray[i].coef * b.termArray[j].coef;  
            int exp = termArray[i].exp + b.termArray[j].exp;  
            c.NewTerm(coef,exp);  
        }  
    }  
    return c;  
}  

Polynomial Polynomial::operator/(const Polynomial & d)  
{  
	if (d.terms = 0){
		throw std::invalid_argument("divisor equals to zero");
	}
    Polynomial q;
    Polynomial r;
    
    r = *this;
    while ((r.terms != 0) && (r.termArray[0].exp >= d.termArray[0].exp)){
    	
	}
    
}  



void Polynomial::NewTerm(unsigned long coef, int exp)  
{  
    if(terms == capacity){  
        capacity *= 2;  
        Term *tmp = new Term[capacity];  
        copy(termArray,termArray+terms,tmp);  
        delete [] termArray;  
        termArray = tmp;  
    }  
    Term ATerm;  
    ATerm.coef=coef;
	ATerm.exp=exp;  
    insertTerm(ATerm);  
}  

void Polynomial::insertTerm(const Term &term)  
{  
    int i;  
    for(i = 0; i < terms && term.exp < termArray[i].exp; i++){ 
		if(term.exp == termArray[i].exp){  
        	termArray[i].coef += term.coef;  
        	if(!termArray[i].coef){  
          	  for(int j = i; j < terms-1; j++)  
          	      termArray[j] = termArray[j+1];  
          	  terms--;  
      	  }  
   	 	}
		else{  
  	      for(int j = terms-1; j >= i;  j--) {
  	      	termArray[j+1] = termArray[j];  
			} 
            
 	       termArray[i] = term;  
 	       terms++;  
 	   }   
    }  
    
}  
  
float Polynomial::Eval(float x)  
{  
    float res=0.0;  
    for(int i=0;i<terms; i++){  
        res += termArray[i].coef * pow(x,termArray[i].exp);  
    }  
    return res;  
}  
  
ostream & operator<<(ostream & o,const Polynomial & poly)  
{  
    for(int i=0;i<poly.terms-1;i++){  
        o<<poly.termArray[i].coef<<"x^"<<poly.termArray[i].exp<<" + ";  
    }  
    o<<poly.termArray[poly.terms-1].coef<<"x^"<<poly.termArray[poly.terms-1].exp;  
    return o;  
}  
