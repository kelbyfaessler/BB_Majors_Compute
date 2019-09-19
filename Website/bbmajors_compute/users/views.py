from django.shortcuts import render
#from .forms import UserForm
#from .models import User
from django.contrib.auth import login
from django.shortcuts import redirect

def index(request):
    """
    main homepage
    """

    return redirect('teams')

