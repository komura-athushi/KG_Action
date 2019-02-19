/*!
 * @brief	静的オブジェクト。
 */


#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/physics/tkPhysicsStaticObject.h"

namespace tkEngine{
	CPhysicsStaticObject::CPhysicsStaticObject()
	{
	}
	CPhysicsStaticObject::~CPhysicsStaticObject()
	{
		PhysicsWorld().RemoveRigidBody(m_rigidBody);
	}
	void CPhysicsStaticObject::CreateMeshObject(prefab::CSkinModelRender* skinModelRender, CVector3 pos, CQuaternion rot, CVector3 scale)
	{
		CreateMeshObject(skinModelRender->GetSkinModel(), pos, rot, scale);
	}
	void CPhysicsStaticObject::CreateMeshObject(CSkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scale)
	{
		CMatrix mScale;
		mScale.MakeScaling(scale);
		m_meshCollider.CreateFromSkinModel(skinModel, &mScale);
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_meshCollider;
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		PhysicsWorld().AddRigidBody(m_rigidBody);
	}
	void CPhysicsStaticObject::CreateBoxObject(CVector3 pos, CQuaternion rot, CVector3 size)
	{
		//Boxコライダーを作成。
		m_boxCollider.Create(size);

		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_boxCollider;
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		PhysicsWorld().AddRigidBody(m_rigidBody);
	}
	void CPhysicsStaticObject::SetPosition(CVector3& pos)
	{
		btTransform& worldTrans = m_rigidBody.GetBody()->getWorldTransform();
		auto& origin = worldTrans.getOrigin();
		origin.setX(pos.x);
		origin.setY(pos.y);
		origin.setZ(pos.z);
	}
}