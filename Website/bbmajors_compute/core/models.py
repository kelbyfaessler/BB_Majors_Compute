from django.db import models
from django.contrib.auth.models import AbstractUser, BaseUserManager
from django.contrib.auth.validators import UnicodeUsernameValidator
from django.utils.translation import gettext_lazy as _

"""
Custom user manager because I'm making username optional and email required, where the default
user has username required and email optional. Heavily re-used the django default UserManager
"""
class UserManager(BaseUserManager):
    use_in_migrations = True

    def _create_user(self, email, first_name, last_name, username, password, **extra_fields):
        """
        Create and save a user with the given email, first name, last name, username, and password.
        """
        if not email:
            raise ValueError('Email is required')
        if not first_name:
            raise ValueError('First name is required')
        if not last_name:
            raise ValueError('Last name is required')
        if not password:
            raise ValueError('Password is required')

        email = self.normalize_email(email)
        username = self.model.normalize_username(username)
        user = self.model(username=username,
                          email=email,
                          first_name=first_name,
                          last_name=last_name,
                          **extra_fields)
        user.set_password(password)
        user.save()
        return user

    def create_user(self, email, first_name, last_name, username=None, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', False)
        extra_fields.setdefault('is_superuser', False)
        return self._create_user(email, first_name, last_name, username, password, **extra_fields)

    def create_superuser(self, email, first_name, last_name, username=None, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        if extra_fields.get('is_staff') is not True:
            raise ValueError('Superuser must have is_staff=True.')
        if extra_fields.get('is_superuser') is not True:
            raise ValueError('Superuser must have is_superuser=True.')

        return self._create_user(email, first_name, last_name, username, password, **extra_fields)

class User(AbstractUser):
    username_validator = UnicodeUsernameValidator()
    username = models.CharField(_('username'),
                                max_length=50,
                                unique=False,
                                help_text=_('Optional. 50 characters or fewer. Letters, digits and @/./+/-/_ only.'),
                                validators=[username_validator],
                                blank=True,
                                null=True)

    email=models.EmailField(_('email address'), unique=True, blank=False, error_messages={
        'unique': _("A user with that email address already exists")
    })

    first_name = models.CharField(_('first name'), max_length=30, blank=False)
    last_name = models.CharField(_('last name'), max_length=50, blank=False)

    USERNAME_FIELD = 'email'

    # REQUIRED_FIELDS should not include the USERNAME_FIELD or password since these will always be prompted for,
    # per the documentation: https://docs.djangoproject.com/en/2.1/topics/auth/customizing/#django.contrib.auth.models.CustomUser.REQUIRED_FIELDS
    REQUIRED_FIELDS = ['first_name', 'last_name']

    objects = UserManager()

