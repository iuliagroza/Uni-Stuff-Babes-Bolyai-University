from repository.taxi_repository import TaxiRepository
from services.taxi_services import TaxiServices
from ui.ui import UI

if __name__ == "__main__":
    """
    Main call
    """
    repository = TaxiRepository()
    services = TaxiServices(repository)
    ui = UI(services)
    ui.start()
