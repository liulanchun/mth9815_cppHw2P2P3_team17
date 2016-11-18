/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;

int main()
{

  // Create the 10Y treasury note
  date maturityDate(2026, Nov, 16);
  string cusip = "912828M56";
  Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

  // Create the 2Y treasury note
  date maturityDate2(2018, Nov, 5);
  string cusip2 = "912828TW0";
  Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

  // Create a BondProductService
  BondProductService *bondProductService = new BondProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond);
  Bond bond = bondProductService->GetData(cusip);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 2Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond2);
  bond = bondProductService->GetData(cusip2);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;


  // Create the Spot 10Y Outright Swap
  date effectiveDate(2016, Nov, 16);
  date terminationDate(2026, Nov, 16);
  string outright10Y = "Spot-Outright-10Y";
  IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

  // Create the IMM 2Y Outright Swap
  date effectiveDate2(2016, Dec, 20);
  date terminationDate2(2018, Dec, 20);
  string imm2Y = "IMM-Outright-2Y";
  IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

  // Create a IRSwapProductService
  IRSwapProductService *swapProductService = new IRSwapProductService();

  // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(outright10YSwap);
  IRSwap swap = swapProductService->GetData(outright10Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  swap = swapProductService->GetData(imm2Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  //create EuroDollar Future, Bond Future and Oil Future
  date edMtDt(2016, Dec, 16);
  date bondMtDt(2017, Mar, 16);
  date oilMtDt(2017, Jun, 16);
  EuroDollarFuture edFuture("EDDEC2016",edMtDt, 99.025);
  BondFuture bondFuture("BONDMAR2017",bondMtDt, 153.22);
  Future oilFuture("OILJUN2017", OILFTR, oilMtDt, 48.55);

  // Create a FutureProductService
  FutureProductService *futureProductService = new FutureProductService();

  // Add the EuroDollar to the FutureProductService and retrieve it from the service
  futureProductService->Add(edFuture);
  Future future = futureProductService->GetData("EDDEC2016");
  cout << "Eurodollar Future: " << future.GetProductId() << " ==> " << future << endl;

  // Add the BondDollar to the FutureProductService and retrieve it from the service
  futureProductService->Add(bondFuture);
  future = futureProductService->GetData("BONDMAR2017");
  cout << "Bond Future: " << future.GetProductId() << " ==> " << future << endl;

  // Add the OIL Future to the FutureProductService and retrieve it from the service
  futureProductService->Add(oilFuture);
  future = futureProductService->GetData("OILJUN2017");
  cout << "Oil Future: " << future.GetProductId() << " ==> " << future << endl;

  //test added util functions
  vector<Bond> vbonds = bondProductService->GetBonds(string("T"));
  cout << "Number of Bonds with ticker T: " << vbonds.size() << endl;

  vector<IRSwap> vswaps = swapProductService->GetSwaps(THIRTY_THREE_SIXTY);
  cout << "Number of Swaps with day count convention of THIRTY_THREE_SIXTY: " << vswaps.size() << endl;

  return 0;
}
