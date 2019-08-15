from django.db import models
#from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.contrib.auth.models import AbstractUser
from django.utils import timezone
from django.utils.translation import gettext_lazy as _

"""
Custom user manager so logins happen with email instead of username.
Heavily re-used the django default UserManager
"""
# class UserManager(BaseUserManager):
#     #use_in_migrations = True

#     def _create_user(self, email, password, is_staff, is_superuser, **extra_fields):
#         """
#         Create and save a user with the given email, first name, last name, username, and password.
#         """
#         if not email:
#             raise ValueError('Email is required')

#         now = timezone.now()

#         email = self.normalize_email(email)
#         user = self.model(email=email,
#                           is_staff=is_staff,
#                           is_superuser=is_superuser,
#                           is_active=True,
#                           last_login=now,
#                           date_joined=now,
#                           **extra_fields)
#         user.set_password(password)
#         user.save(using=self._db)
#         return user

#     def create_user(self, email, password, **extra_fields):
#         is_staff = False
#         is_superuser = False
#         return self._create_user(email, password, is_staff, is_superuser, **extra_fields)

#     def create_superuser(self, email, password=None, **extra_fields):
#         is_staff = True
#         is_superuser = True
#         return self._create_user(email, password, is_staff, is_superuser, **extra_fields)

class CustomUser(AbstractUser):
    pass

# class User(AbstractBaseUser, PermissionsMixin):
#     email=models.EmailField(_('email address'), unique=True, max_length=254, blank=False, error_messages={
#         'unique': _("A user with that email address already exists")
#     })
#     first_name = models.CharField(_('first name'), max_length=50, blank=False)
#     last_name = models.CharField(_('last name'), max_length=50, blank=False)
#     is_staff = models.BooleanField(default=False)
#     is_superuser = models.BooleanField(default=False)
#     is_active = models.BooleanField(default=False)
#     last_login = models.DateTimeField(null=True, blank=True)
#     date_joined = models.DateTimeField(auto_now_add=True)

#     USERNAME_FIELD = 'email'
#     EMAIL_FIELD = 'email'

#     # REQUIRED_FIELDS should not include the USERNAME_FIELD or password since these will always be prompted for,
#     # per the documentation: https://docs.djangoproject.com/en/2.1/topics/auth/customizing/#django.contrib.auth.models.CustomUser.REQUIRED_FIELDS
#     REQUIRED_FIELDS = []

#     objects = UserManager()

#     def get_absolute_url(self):
#         return "/users/%i/" % (self.pk)

