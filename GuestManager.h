#pragma once

#include<vector>

enum class RoomType
{
    Standard,
    Comfort
};

enum class GuestType
{
    Family,
    Businessman,
    Rockstar
};


class Guest
{
public:
    Guest(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays);
    virtual ~Guest() {};

    GuestType GetGuestType() const;
    RoomType GetRoomType() const;
    int GetBookedDays() const;
    virtual int GetRoomBusyDays() const = 0;
    virtual int GetAdditionalIncome() const = 0;

protected:
    GuestType mMyType;
    RoomType mRoomOccupied;
    int mStayDays;
};

class Family : public Guest
{
public:
    Family(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays);

    virtual int GetRoomBusyDays() const override;
    virtual int GetAdditionalIncome() const override;
};

class Businessman : public Guest
{
public:
    Businessman(GuestType typeOfGuest,
        RoomType typeOfRoom,
        int stayDays,
        int additionalIncome = 0);

    virtual int GetRoomBusyDays() const override;
    virtual int GetAdditionalIncome() const override;

private:
    int mAdditionalIncome;
};

class Rockstar : public Guest
{
public:
    Rockstar(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays);

    virtual int GetRoomBusyDays() const override;
    virtual int GetAdditionalIncome() const override;
};




class GuestManager
{
public:
    GuestManager(int numOfStandard, int priceOfStandard, int numOfComfort, int priceOfComfort);
    bool AddGuest(GuestType typeOfGuest, RoomType typeOfRoom, int stayDays, int additionalIncome = 0);
    bool IsAvailable(RoomType typeOfRoom, int inDays = 0) const;
    int IncomingProfit() const;
    float EarningEfficiency() const;
    bool operator<(const GuestManager& other) const;

private:
    int mNumOfStandard;
    int mPriceOfStandard;
    int mNumOfComfort;
    int mPriceOfComfort;

    std::vector<Guest*> mGuests;
};
