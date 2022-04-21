from configparser import ConfigParser
from src.repository.base_repository.student_repository import StudentRepo
from src.repository.base_repository.discipline_repository import DisciplineRepo
from src.repository.base_repository.grade_repository import GradeRepo
from src.repository.csv_repository.csv_student_repository import CSVStudentRepo
from src.repository.csv_repository.csv_discipline_repository import CSVDisciplineRepo
from src.repository.csv_repository.csv_grade_repository import CSVGradeRepo
from src.repository.binary_repository.bin_student_repository import BinStudentRepo
from src.repository.binary_repository.bin_discipline_repository import BinDisciplineRepo
from src.repository.binary_repository.bin_grade_repository import BinGradeRepo
from src.services.undo_redo_services import UndoServices
from src.services.student_services import StudentServices
from src.services.discipline_services import DisciplineServices
from src.services.grade_services import GradeServices
from src.ui.ui import UI


class Settings:
    def __init__(self):
        parser = ConfigParser()
        parser.read("settings.properties")
        repo_style = parser.get("options", "repository")
        stud = parser.get("options", "students")
        disc = parser.get("options", "disciplines")
        grd = parser.get("options", "grades")
        if repo_style == "memory":
            ok = True

            stud_repo = StudentRepo()
            disc_repo = DisciplineRepo()
            grade_repo = GradeRepo()

            undo_serv = UndoServices()
            stud_serv = StudentServices(stud_repo, grade_repo, undo_serv)
            disc_serv = DisciplineServices(disc_repo, grade_repo, undo_serv)
            grade_serv = GradeServices(stud_repo, disc_repo, grade_repo, undo_serv)

            self._ui = UI(stud_serv, disc_serv, grade_serv, ok)
        elif repo_style == "csv":
            ok = False

            stud_repo = CSVStudentRepo(stud)
            disc_repo = CSVDisciplineRepo(disc)
            grade_repo = CSVGradeRepo(grd, stud_repo, disc_repo)

            undo_serv = UndoServices()
            stud_serv = StudentServices(stud_repo, grade_repo, undo_serv)
            disc_serv = DisciplineServices(disc_repo, grade_repo, undo_serv)
            grade_serv = GradeServices(stud_repo, disc_repo, grade_repo, undo_serv)

            self._ui = UI(stud_serv, disc_serv, grade_serv, ok)
        elif repo_style == "pickle":
            ok = False

            stud_repo = BinStudentRepo(stud)
            disc_repo = BinDisciplineRepo(disc)
            grade_repo = BinGradeRepo(grd, stud_repo, disc_repo)

            undo_serv = UndoServices()
            stud_serv = StudentServices(stud_repo, grade_repo, undo_serv)
            disc_serv = DisciplineServices(disc_repo, grade_repo, undo_serv)
            grade_serv = GradeServices(stud_repo, disc_repo, grade_repo, undo_serv)

            self._ui = UI(stud_serv, disc_serv, grade_serv, ok)

    @property
    def ui(self):
        return self._ui
