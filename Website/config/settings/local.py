from .base import *

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'k@pof%x7hz2)i#xow2j%g00h_psj^_oz=qbesij#8%5e%&10xv'

DEBUG = True

# EMAIL_BACKEND = 'django.core.mail.backends.console.EmailBackend'

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql_psycopg2',
        'NAME': 'bbmajors_compute_dev',
        'USER': 'kelby',
        'PASSWORD': 'windowsdevpass',
        'HOST': 'localhost',
        'PORT': '',
    }
}

# https://docs.djangoproject.com/en/dev/topics/email/#file-backend 
#EMAIL_BACKEND = 'django.core.mail.backends.filebased.EmailBackend'
#EMAIL_FILE_PATH = BASE_DIR.path('test', 'email')
EMAIL_BACKEND = 'django.core.mail.backends.console.EmailBackend'

# INSTALLED_APPS += ['debug_toolbar', ]
