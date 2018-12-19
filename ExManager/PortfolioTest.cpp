#include "gmock/gmock.h"
#include "Portfolio.h"

using namespace ::testing;
using namespace std;
using namespace boost::gregorian;

class APortfolio: public Test
{
public:
    static const date ArbitraryDate;
    static const string IBM;
    static const string SAMSUNG;
    Portfolio portfolio_;

    void Purchase(const string& symbol, unsigned int shareCount,
            const date& transactionDate = APortfolio::ArbitraryDate)
    {
        portfolio_.Purchase(symbol, shareCount, transactionDate);
    };

};

const date APortfolio::ArbitraryDate(2018, Dec, 1);
const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");


TEST_F(APortfolio, IsEmptyWhenCreated)
{
    ASSERT_TRUE(portfolio_.IsEmpty());
}
TEST_F(APortfolio, IsNotEmptyAfterPurchase)
{
    portfolio_.Purchase(IBM, 1);

    ASSERT_FALSE(portfolio_.IsEmpty());
}
TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol)
{
    ASSERT_THAT(portfolio_.ShareCount("AAPL"), Eq(0u));
}
TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol)
{
    portfolio_.Purchase(IBM, 2);
    ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(2u));
}
TEST_F(APortfolio, ThrowOnPurchaseOfZeroShares)
{
    ASSERT_THROW(portfolio_.Purchase(IBM, 0), InvalidPurchaseException);
}
TEST_F(APortfolio, AnswersShareCountForAppropriateSymbol)
{
    portfolio_.Purchase(IBM, 5);
    portfolio_.Purchase(SAMSUNG, 10);

    ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u));
}
TEST_F(APortfolio, ShareCountReflectsAccumulatedPurchaseOfSameSymbol)
{
    portfolio_.Purchase(IBM, 5);
    portfolio_.Purchase(IBM, 10);

    ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u + 10));
}
TEST_F(APortfolio, ReduceShareCountOfSymbolsOnSell)
{
    Purchase(SAMSUNG, 30);
    portfolio_.Sell(SAMSUNG, 13);

    ASSERT_THAT(portfolio_.ShareCount(SAMSUNG), Eq(30u-13));
}
TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased)
{
    ASSERT_THROW(portfolio_.Sell(SAMSUNG,1), InvalidSellException);
}
TEST_F(APortfolio, AnswersThePurchaseRecordsForASinglePurchase)
{
    date dateOfPurchase(2018, Nov, 22);
    Purchase(SAMSUNG, 5, dateOfPurchase);

    auto purchases = portfolio_.Purchases(SAMSUNG);
    auto purchase = purchases[0];

    ASSERT_THAT(purchase.ShareCount, Eq(5));
    ASSERT_THAT(purchase.Date, Eq(dateOfPurchase));
}