select * from cursos where not (creditos < 6 or tipo = 'optativa') and cupo > 0;
