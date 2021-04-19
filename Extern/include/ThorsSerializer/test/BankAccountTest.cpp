#include "gtest/gtest.h"
#include "BankAccountTest.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

ThorsAnvil_RegisterPolyMorphicType(OnLineBank::CurrentAccount);
ThorsAnvil_RegisterPolyMorphicType(OnLineBank::DepositAccount);

TEST(BankAccountTest, JsonExportCustomField)
{
    bool    serializeOK     = false;
    bool    deserializeOK   = false;

    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream stream;
    if (stream << ThorsAnvil::Serialize::jsonExporter(src))
    {
        serializeOK = true;
    }

    OnLineBank::CurrentAccount dst;
    if (stream >>ThorsAnvil::Serialize::jsonImporter(dst))
    {
        deserializeOK = true;
    }

    EXPECT_TRUE(serializeOK);
    EXPECT_TRUE(deserializeOK);

    EXPECT_EQ(234, dst.getAccountIdent());
    EXPECT_EQ(888 + 32 - 12, dst.getBalance());
    EXPECT_TRUE(dst.isValid());
}

TEST(BankAccountTest, BsonExportCustomField)
{
    bool    serializeOK     = false;
    bool    deserializeOK   = false;

    OnLineBank::CurrentAccount  src(OnLineBank::ID{234}, 888, "This is an account", true);

    src.addTransaction(1, 32, OnLineBank::Deposit);
    src.addTransaction(2, 12, OnLineBank::Withdraw);

    std::stringstream stream;
    if (stream << ThorsAnvil::Serialize::bsonExporter(src))
    {
        serializeOK = true;
    }

    OnLineBank::CurrentAccount dst;
    if (stream >> ThorsAnvil::Serialize::bsonImporter(dst))
    {
        deserializeOK = true;
    }

    EXPECT_TRUE(serializeOK);
    EXPECT_TRUE(deserializeOK);

    EXPECT_EQ(234, dst.getAccountIdent());
    EXPECT_EQ(888 + 32 - 12, dst.getBalance());
    EXPECT_TRUE(dst.isValid());
}

