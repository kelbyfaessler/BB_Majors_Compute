from django.shortcuts import render
from django.shortcuts import redirect
from django.contrib.auth.decorators import login_required

@login_required
def teams(request):
    """
    page where best teams are calculated
    """
    return render(
        request,
        'teams.html',
        context={}
    )
