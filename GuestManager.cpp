#include "GuestManager.h"

Guest::Guest(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays):
    mMyType(typeOfGuest), mRoomOccupied(typeOfRoom), mStayDays(stayDays)
{
}

GuestType Guest::GetGuestType() const
{
    return mMyType;
}

RoomType Guest::GetRoomType() const
{
    return mRoomOccupied;
}

int Guest::GetBookedDays() const
{
    return mStayDays;
}

Family::Family(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays) :
    Guest(typeOfGuest, typeOfRoom, stayDays)
{
}

int Family::GetRoomBusyDays() const
{
    return mStayDays;
}

int Family::GetAdditionalIncome() const
{
    return 0;
}

Businessman::Businessman(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays, int additionalIncome):
    Guest(typeOfGuest, typeOfRoom, stayDays), mAdditionalIncome(additionalIncome)
{
}

int Businessman::GetRoomBusyDays() const
{
    return mStayDays;
}

int Businessman::GetAdditionalIncome() const
{
    return mAdditionalIncome;
}

Rockstar::Rockstar(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays) :
    Guest(typeOfGuest, typeOfRoom, stayDays)
{
}

int Rockstar::GetRoomBusyDays() const
{
    return mStayDays + 10;
}

int Rockstar::GetAdditionalIncome() const
{
    return 0;
}

GuestManager::GuestManager(int numOfStandard, int priceOfStandard, int numOfComfort, int priceOfComfort):
    mNumOfStandard(numOfStandard), mPriceOfStandard(priceOfStandard),
    mNumOfComfort(numOfComfort), mPriceOfComfort(priceOfComfort)
{
}

bool GuestManager::AddGuest(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays, int additionalIncome)
{
    if(!IsAvailable(typeOfRoom))
        return false;

    switch (typeOfGuest)
    {
    case GuestType::Family:
        mGuests.push_back(new Family{ typeOfGuest, typeOfRoom, stayDays });
        break;

    case GuestType::Businessman:
        mGuests.push_back(new Businessman{ typeOfGuest, typeOfRoom, stayDays, additionalIncome });
        break;

    case GuestType::Rockstar:
        mGuests.push_back(new Rockstar{ typeOfGuest, typeOfRoom, stayDays });
        break;
    }

    return true;
}

bool GuestManager::IsAvailable(RoomType typeOfRoom, int inDays) const
{
    int numberOccupied{ 0 };

    for (auto guest : mGuests)
    {
        if (guest->GetRoomType() == typeOfRoom && guest->GetRoomBusyDays() > inDays)
            numberOccupied++;
    }

    switch (typeOfRoom)
    {
    case RoomType::Standard:
        if (numberOccupied < mNumOfStandard)
            return true;
        break;

    case RoomType::Comfort:
        if (numberOccupied < mNumOfComfort)
            return true;
        break;
    }

    return false;
}

int GuestManager::IncomingProfit() const
{
    int result{ 0 };

    for (auto guest : mGuests)
    {
        switch (guest->GetRoomType())
        {
        case RoomType::Standard:
            result += guest->GetBookedDays() * (mPriceOfStandard + guest->GetAdditionalIncome());
            break;

        case RoomType::Comfort:
            result += guest->GetBookedDays() * (mPriceOfComfort + guest->GetAdditionalIncome());
            break;
        }
    }

    return result;
}

float GuestManager::EarningEfficiency() const
{
    int occupiedStandard{ 0 };
    int occupiedComfort{ 0 };
    int totalAdditionalIncome{ 0 };

    for (auto guest : mGuests)
    {
        switch (guest->GetRoomType())
        {
        case RoomType::Standard:
            occupiedStandard++;
            break;

        case RoomType::Comfort:
            occupiedComfort++;
            break;
        }

        totalAdditionalIncome += guest->GetAdditionalIncome();
    }

    int currentDayEarning{ occupiedStandard * mPriceOfStandard + occupiedComfort * mPriceOfComfort + totalAdditionalIncome };
    int maxDayEarning{ mNumOfStandard * mPriceOfStandard + mNumOfComfort * mPriceOfComfort };

    return (float)currentDayEarning / maxDayEarning;
}

bool GuestManager::operator<(const GuestManager& other) const
{
    return IncomingProfit() < other.IncomingProfit();
}