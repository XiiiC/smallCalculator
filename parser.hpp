#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
class Parser
{
    public:
    int x;
    int y;
    Parser()
    {
        std::string str;
        std::cout<<"Enter infix string: ";
        std::cin >> str;//user input gathered when class constructed
        stream = std::stringstream(str);
        lookAhead = stream.get();
    }
    void parse()
    {
        Expr();
        PrintTranslatedString();

        Calculate();

    }
    private:
    char lookAhead;//char that is being handled
    std::string translated;//char thats being output
    std::stringstream stream;//stream of user's input
    void Display(char terminal)
    {
        translated += terminal;
    }
    void PrintTranslatedString()
    {
        std::cout<<translated<<std::endl;

    }
    std::string ErrorMessage(char lookAhead)
    {
        return "Syntax Error near: " + std::string(1,lookAhead);//identifies location of invalid char
    }
     void Match(char terminal) {
        if (terminal == lookAhead) {
            lookAhead = stream.get();
        }
        else {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }
    /* digit Rules
    digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    */
    void Digit()
    {
        Display(lookAhead);
        Match(lookAhead);
    }
    /* factor Rules
    factor -> (expr)
             |digit
    */
    void Factor()
    {
        if(isdigit(lookAhead))
            Digit();
        else if(lookAhead == '(')
        {
            Match('(');
            Expr();
            Match(')');
        }
        else
        {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }
    /* term Rules
    term -> term * factor
           |term / factor
           |factor
    */
    void Term()
    {
        Factor();
        if(lookAhead == '*')
        {
            Match('*');
            Factor();
            Display('*');
        }
        else if(lookAhead == '/')
        {
            Match('/');
            Factor();
            Display('/');
        }
    }
    /* expr Rules
    expr -> expr + term
           |expr - term
           |term
    */
    void Expr()
    {
        Term();
        while(true)
        {
            if(lookAhead == '+')
            {
                Match('+');
                Term();
                Display('+');
            }
            else if(lookAhead == '-')
            {
                Match('-');
                Term();
                Display('-');
            }
            else return;
        }  
    }
    void Calculate()
    {
        while(true)
        {
            for (int i = 0; i < translated.length(); i++)
            {
                if (!isdigit(translated[i]))
                {
                   if(translated[i] == '+')
                   {
                      Addition(i);
                    }
                    if(translated[i] == '-')
                    {
                        Subtraction(i);
                    }
                    if(translated[i] == '*')
                    {
                        Multiplication(i);
                    }
                    if(translated[i] == '/')
                    {
                        Division(i);
                    }
                }

                if (i >= translated.length())
                {
                    return;
                }
                
            } 
        }
    }
    void Addition(int pos)
    {
        x = translated[pos-2] - 48;
        y = translated[pos-1] - 48;
        
        std::cout<<x<<" + "<<y<<" = "<<x+y<<std::endl;
        translated.erase(pos-2,3);
        
        translated.insert(pos-2, std::to_string(x+y));
        std::cout<<translated<<std::endl;
    }
    void Subtraction(int pos)
    {
        x = translated[pos-2] - 48;
        y = translated[pos-1] - 48;
        
        std::cout<<x<<" - "<<y<<" = "<<x-y<<std::endl;
        translated.erase(pos-2,3);
        
        translated.insert(pos-2, std::to_string(x-y));
        std::cout<<translated<<std::endl;
    }
    void Multiplication(int pos)
    {
        x = translated[pos-2] - 48;
        y = translated[pos-1] - 48;
        
        std::cout<<x<<" * "<<y<<" = "<<x*y<<std::endl;
        translated.erase(pos-2,3);
        
        translated.insert(pos-2, std::to_string(x*y));
        std::cout<<translated<<std::endl;
    }
    void Division(int pos)
    {
        x = translated[pos-2] - 48;
        y = translated[pos-1] - 48;
        
        std::cout<<x<<" / "<<y<<" = "<<x/y<<std::endl;
        translated.erase(pos-2,3);
        
        translated.insert(pos-2, std::to_string(x/y));
        std::cout<<translated<<std::endl;
    }
};