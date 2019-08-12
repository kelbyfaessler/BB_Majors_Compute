from django.shortcuts import render
from .forms import UserForm
from .models import User
from django.contrib.auth import login
from django.shortcuts import redirect

def index(request):
    """
    main homepage
    """

    return redirect('teams')

def signin(request):
    """
    signup page: allow existing user to sign in
    """
    
    return render(
        request,
        'signin.html',
        context={}
    )


def signup(request):
    """
    signup page: form to collect user info if they want to sign up
    """
    if request.method == "POST":
        form = UserForm(request.POST)
        if form.is_valid():
            email = form.cleaned_data.get('email')
            username = form.cleaned_data.get('username')
            first_name = form.cleaned_data.get('first_name')
            last_name = form.cleaned_data.get('last_name')
            password = form.cleaned_data.get('password')
            new_user = User.objects.create_user(email=email,
                                                username=username,
                                                first_name=first_name,
                                                last_name=last_name,
                                                password=password)
            new_user.save()
            login(request=request, user=new_user)
            #redirect
            return redirect('construction')
        else:
            # Append css error class to each field that has errors
            for field in form.errors:
                if field == '__all__':
                    continue
                form[field].field.widget.attrs['class'] += ' field-error'
    else:
        form = UserForm()

    return render(
        request,
        'signup.html',
        context={'form': form}
    )

def terms(request):
    """
    terms and conditions page: basic terms, gives credibility to site
    """

    return render(
        request,
        'terms.html',
        context={}
    )