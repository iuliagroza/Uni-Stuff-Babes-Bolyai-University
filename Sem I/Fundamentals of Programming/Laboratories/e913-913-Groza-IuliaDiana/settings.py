from configparser import ConfigParser

from repository.repository import Repository
from services.services import Services
from txt_repository.txt_repository import CSVRepository
from ui.ui import UI


class Settings:
    def __init__(self):
        parser = ConfigParser()
        parser.read("settings.properties")
        repo_style = parser.get("options", "choice")
        repository = parser.get("options", "repository")
        if repo_style == "memory":
            repo = Repository()
            services = Services(repo)
            self._ui = UI(services)

        elif repo_style == "txt":
            repo = CSVRepository(repository)
            services = Services(repo)
            self._ui = UI(services)

    @property
    def ui(self):
        return self._ui
