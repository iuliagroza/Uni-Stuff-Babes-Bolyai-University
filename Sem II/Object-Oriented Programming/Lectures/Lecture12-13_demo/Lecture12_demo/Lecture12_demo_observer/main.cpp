#include "lecture12_demo_observer.h"
#include <QtWidgets/QApplication>
#include "auctionleader.h"
#include "Auctioneer.h"
#include "BidderWithDescription.h"
#include "BidderWithPhoto.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Auctioneer auct;
	auct.addCastle("Highclere Castle", "highclere.jpg", "England", 4000, 4000);
	auct.addCastle("Chambord Castle", "chambord.jpg", "France", 3200, 3200);

	BidderWithDescription bidderDesc1{ auct };
	bidderDesc1.show();

	BidderWithDescription bidderDesc2{ auct };
	bidderDesc2.show();

	BidderWithPhoto bidderPhoto{ auct };
	bidderPhoto.show();

	AuctionLeader leader{ auct };
	leader.show();

	return a.exec();
}
