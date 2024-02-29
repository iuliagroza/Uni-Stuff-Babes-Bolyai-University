from django.urls import path

from .views import IncomeListView, IncomeDetailView

urlpatterns = [
    path('all/', IncomeListView.as_view(), name='incomeList'),
    path('all/<int:pk>/', IncomeDetailView.as_view(), name='incomeDetail'),

]