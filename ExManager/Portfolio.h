#ifndef FIRSTEXAMPLE_PORTFOLIO_H
#define FIRSTEXAMPLE_PORTFOLIO_H

#include <string>

class Portfolio
{
private:
    bool isEmpty_;
    unsigned int shareCount_;
public:
    Portfolio();
    bool IsEmpty() const;
    void Purchase(const std::string& symbol, unsigned int shareCount);
    unsigned int ShareCount(const std::string& symbol) const;

};


#endif //FIRSTEXAMPLE_PORTFOLIO_H
