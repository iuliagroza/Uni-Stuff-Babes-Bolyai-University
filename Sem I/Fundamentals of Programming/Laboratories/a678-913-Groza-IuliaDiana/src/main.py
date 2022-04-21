from src.repository.student_repository import StudentRepo
from src.repository.discipline_repository import DisciplineRepo
from src.repository.grade_repository import GradeRepo
from src.services.undo_redo_services import UndoServices
from src.services.student_services import StudentServices
from src.services.discipline_services import DisciplineServices
from src.services.grade_services import GradeServices
from src.ui.ui import UI


if __name__ == "__main__":
    # Main call
    stud_repo = StudentRepo()
    disc_repo = DisciplineRepo()
    grade_repo = GradeRepo()

    undo_serv = UndoServices()
    stud_serv = StudentServices(stud_repo, grade_repo, undo_serv)
    disc_serv = DisciplineServices(disc_repo, grade_repo, undo_serv)
    grade_serv = GradeServices(stud_repo, disc_repo, grade_repo, undo_serv)

    ui = UI(stud_serv, disc_serv, grade_serv)
    ui.start()
