# Wakfu JNI Tool

## Presentation

Ce projet se concentre sur l'interaction avec le jeu Wakfu en utilisant le Java Native Interface (JNI). Le JNI permet d'executer du code C/C++ dans une application Java en cours d'execution.

## Fonctionnement

Le code suivant illustre comment le tool fonctionne :
```cpp
class_ptr = p_env->FindClass("aYA");
jfieldID class_instance_field_id = p_env->GetStaticFieldID(class_ptr, "d", "LaYA;");
class_instance = p_env->GetStaticObjectField(class_ptr, class_instance_field_id);
```
### Explication

- p_env sert de pont entre le code C++ et Java (JNIEnv) et est directement fourni par Java.
- p_env->FindClass("aYA") recherche la classe Java "aYA", qui correspond a "WakfuGameEntity" dans le jeu Wakfu.
- p_env->GetStaticFieldID(class_ptr, "d", "LaYA;") recupere l'ID du champ statique "d" de cette classe.
- p_env->GetStaticObjectField(class_ptr, class_instance_field_id) recupere l'instance de la classe en utilisant l'ID du champ statique.
