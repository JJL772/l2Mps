#include "l2Mps_blen.h"

IMpsBlen::IMpsBlen(Path mpsRoot, const uint8_t amc)
    : IMpsAppBase<blen_channel_t>(amc)
{
    for (int ch = 0; ch < maxChannelCount; ++ch)
    {
        try
        {
            ThrChannel aThr(IThrChannel::create(mpsRoot, ch));

            if (( aThr->getThrCount().first) && (aThr->getThrCount().second) > 0)
            {
                for (int i = 0; i < numBlenChs; ++i)
                {
                    if ( ( aThr->getByteMap().first ) && ( aThr->getByteMap().second == blenChByteMap[amc][i] ) )
                    {
                        appThrMap.insert( std::make_pair( i, aThr ) );
                        break;
                    }
                }
            }
        }
        catch (CPSWError &e)
        {
        }
    }

    std::cout << "    > A BLEN was created (AMC = " << unsigned(amc) << ")" << std::endl;
    printChInfo();
}

MpsBlen IMpsBlen::create(Path mpsRoot, uint8_t amc)
{
    return boost::make_shared<IMpsBlen>(mpsRoot, amc);
}

// Print BLEN channel information
void IMpsBlen::printChInfo(void) const
{
    for (int i {0}; i < numBlenChs; ++i)
    {
        std::cout << "        Channel = " << i << ": Threshold channel = ";

        blen_thrMap_t::const_iterator it = appThrMap.find(i);

        if (it != appThrMap.end())
            std::cout << unsigned((it->second)->getChannel()) << std::endl;
        else
            std::cout << "Not implemented" << std::endl;
    }
}
