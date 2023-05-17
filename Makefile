CPP=BasicComputerBuilder.cpp CommodityFactory.cpp Fruit.cpp Order.cpp Buyer.cpp Computer.cpp GlobalInfo.cpp Seller.cpp BuyerService.cpp ComputerDirector.cpp Inventory.cpp SellerService.cpp Commodity.cpp Controller.cpp User.cpp main.cpp
TARGET=main

run:
	g++ -g -o $(TARGET) $(CPP)

clean:
	rm $(TARGET)