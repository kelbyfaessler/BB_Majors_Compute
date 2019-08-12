from .base import *

env = environ.Env()

SECRET_KEY = get_env_variable('DJANGO_SECRET_KEY')

ALLOWED_HOSTS = env.list('DJANGO_ALLOWED_HOSTS', default=['.fantasygolfteams.com'])

DB_NAME = get_env_variable('DB_NAME')
DB_USER = get_env_variable('DB_USER')
DB_PASS = get_env_variable('DB_PASS')


DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql_psycopg2',
        'NAME': DB_NAME,
        'USER': DB_USER,
        'PASSWORD': DB_PASS,
        'HOST': 'localhost',
        'PORT': '',
    }
}

