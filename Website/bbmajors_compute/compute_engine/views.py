from django.shortcuts import render
from django.shortcuts import redirect

def teams(request):
    """
    page where best teams are calculated
    """
    if request.user.is_authenticated:
        return render(
            request,
            'teams.html',
            context={}
        )
    else:
        #return redirect('signup')
        return render(
            request,
            'teams.html',
            context={}
        )
